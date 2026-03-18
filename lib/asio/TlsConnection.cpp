#include <iostream>

#include "TlsConnection.hpp"

TlsConnection::TlsConnection(
    boost::asio::io_context &io_context,
    MessageHandler onMessageReceived)
    : clientSocket_(io_context),
      serverSocket_(io_context),
      acceptor_(io_context),
      sslServerContext_(boost::asio::ssl::context::tls_server),
      sslClientContext_(boost::asio::ssl::context::tls_client),
      onMessageReceived_(onMessageReceived)
{
    try
    {
        sslServerContext_.set_options(boost::asio::ssl::context::default_workarounds);
        // Attempt to load server certificate and key if present
        sslServerContext_.use_certificate_chain_file("cert/server.pem");
        sslServerContext_.use_private_key_file("cert/server.key", boost::asio::ssl::context::pem);

        SSL_CTX_set_cipher_list(sslServerContext_.native_handle(),
                        "HIGH:!aNULL:!MD5");

        sslServerContext_.load_verify_file("cert/ca.pem");
        sslServerContext_.set_verify_mode(boost::asio::ssl::verify_peer);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Warning: server certificate/key load failed: " << e.what() << std::endl;
    }

    try
    {
        sslClientContext_.set_default_verify_paths();
        sslClientContext_.load_verify_file("cert/ca.pem");
        sslClientContext_.set_verify_mode(boost::asio::ssl::verify_peer);

        SSL_CTX_set_cipher_list(sslClientContext_.native_handle(),
                        "HIGH:!aNULL:!MD5");

        sslClientContext_.use_certificate_chain_file("cert/client.pem");
        sslClientContext_.use_private_key_file("cert/client.key", boost::asio::ssl::context::pem);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Warning: client CA load failed: " << e.what() << std::endl;
    }

    // Start TLS-enabled server and client (loopback)
    startServer(TLS_TCP_PORT);
    connectClient(TLS_TCP_IP, TLS_TCP_PORT);
}

void TlsConnection::startServer(int port)
{
    std::cout << "Starting TLS server on port " << port << std::endl;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::loopback(), port);

    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    std::cout << "Waiting for new TLS connection" << std::endl;
    acceptor_.async_accept(serverSocket_, [this](const boost::system::error_code &error) {
        if (!error)
        {
            sslServerStream_ = std::make_unique<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(std::move(serverSocket_), sslServerContext_);
            sslServerStream_->async_handshake(boost::asio::ssl::stream_base::server,
                                             [this](const boost::system::error_code &hs_err) {
                                                 if (!hs_err)
                                                 {
                                                     std::cout << "Server TLS handshake successful" << std::endl;
                                                     serverVerified_ = true;
                                                     handleServerRead();
                                                 }
                                                 else
                                                 {
                                                     std::cerr << "Server TLS handshake failed: " << hs_err.message() << std::endl;
                                                 }
                                             });
        }
        else
        {
            std::cerr << "TLS accept failed: " << error.message() << std::endl;
        }
    });
}

void TlsConnection::connectClient(const std::string &host, int port)
{
    std::cout << "Connecting TLS client to " << host << ":" << port << std::endl;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

    try
    {
        clientSocket_.connect(endpoint);
        sslClientStream_ = std::make_unique<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(std::move(clientSocket_), sslClientContext_);
        sslClientStream_->async_handshake(boost::asio::ssl::stream_base::client,
                                         [this](const boost::system::error_code &hs_err) {
                                             if (!hs_err)
                                             {
                                                 std::cout << "Client TLS handshake successful" << std::endl;
                                                 clientVerified_ = true;
                                                 handleClientRead();
                                             }
                                             else
                                             {
                                                 std::cerr << "Client TLS handshake failed: " << hs_err.message() << std::endl;
                                             }
                                         });
    }
    catch (const std::exception &e)
    {
        std::cerr << "TLS client connect failed: " << e.what() << std::endl;
    }
}

void TlsConnection::handleServerRead()
{
    sslServerStream_->async_read_some(boost::asio::buffer(serverBuffer_), std::bind(&TlsConnection::serverReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void TlsConnection::serverReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(serverBuffer_.data(), msgLength);
            Message message(Message::FROM_SERVER_TO_SERVER_UI, msg);
            onMessageReceived_(message);
            handleServerRead();
        }
        else
        {
            std::cout << "Server closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << "Server connection closed by peer" << std::endl;
        sslServerStream_->lowest_layer().close();
    }
    else
    {
        std::cout << "Server Read Error: " << error.message() << std::endl;
    }
}

void TlsConnection::handleClientRead()
{
    sslClientStream_->async_read_some(boost::asio::buffer(clientBuffer_), std::bind(&TlsConnection::clientReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void TlsConnection::clientReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(clientBuffer_.data(), msgLength);
            Message message(Message::FROM_CLIENT_TO_CLIENT_UI, msg);
            onMessageReceived_(message);
            handleClientRead();
        }
        else
        {
            std::cout << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << "Client connection closed by peer" << std::endl;
        sslClientStream_->lowest_layer().close();
    }
    else
    {
        std::cout << "Client Read Error: " << error.message() << std::endl;
    }
}

void TlsConnection::sendFromClientUI(const std::string &msg)
{
    try
    {
        if (not clientVerified_)
        {
            std::cerr << "Cannot send from client UI: TLS handshake not completed" << std::endl;
            return;
        }
        boost::asio::write(*sslClientStream_, boost::asio::buffer(msg));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Client TLS write error: " << e.what() << std::endl;
    }
}

void TlsConnection::sendFromServerUI(const std::string &msg)
{
    try
    {
        if (not serverVerified_)
        {
            std::cerr << "Cannot send from server UI: TLS handshake not completed" << std::endl;
            return;
        }
        boost::asio::write(*sslServerStream_, boost::asio::buffer(msg));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Server TLS write error: " << e.what() << std::endl;
    }
}
