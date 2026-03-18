#include <iostream>
#include <thread>

#include "TcpConnection.hpp"

TcpConnection::TcpConnection(
    boost::asio::io_context &io_context,
    MessageHandler onMessageReceived)
    : clientSocket_(io_context),
      serverSocket_(io_context),
      acceptor_(io_context),
      onMessageReceived_(onMessageReceived)
{
    startServer(TCP_PORT);
    connectClient(TCP_IP, TCP_PORT);
}

void TcpConnection::accept_handler(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection Succeeded\n";
        handleServerRead();
    }
    else
    {
        std::cout << "ERROR: " << error.message();
    }
}

void TcpConnection::handleServerRead()
{
    serverSocket_.async_read_some(boost::asio::buffer(serverBuffer_), std::bind(&TcpConnection::serverReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void TcpConnection::serverReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(serverBuffer_.data(), msgLength);
            Message message(Message::FROM_SERVER_TO_SERVER_UI, msg);
            onMessageReceived_(message);
            TcpConnection::handleServerRead();
        }
        else
        {
            std::cout << serverBuffer_.data() << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << serverBuffer_.data() << "Connection closed by client" << std::endl;
        serverSocket_.close();
    }
    else
    {
        std::cout << serverBuffer_.data() << "Read Error: " << error.message() << std::endl;
    }
}

void TcpConnection::startServer(int port)
{
    std::cout << "Starting TCP server on port " << port << std::endl;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::loopback(), port);

    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    std::cout << "Waiting for new connection" << std::endl;
    acceptor_.async_accept(serverSocket_, std::bind(&TcpConnection::accept_handler, this, std::placeholders::_1));
}

void TcpConnection::connectClient(const std::string &host, int port)
{
    std::cout << "Connecting to TCP server at " << host << ":" << port << std::endl;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

    clientSocket_.connect(endpoint);
    std::cout << "Connected to TCP server" << std::endl;
    handleClientRead();
}

void TcpConnection::handleClientRead()
{
    clientSocket_.async_read_some(boost::asio::buffer(clientBuffer_), std::bind(&TcpConnection::clientReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}


void TcpConnection::clientReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(clientBuffer_.data(), msgLength);
            Message message(Message::FROM_CLIENT_TO_CLIENT_UI, msg);
            onMessageReceived_(message);
            TcpConnection::handleClientRead();
        }
        else
        {
            std::cout << clientBuffer_.data() << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << clientBuffer_.data() << "Connection closed by client" << std::endl;
        clientSocket_.close();
    }
    else
    {
        std::cout << clientBuffer_.data() << "Read Error: " << error.message() << std::endl;
    }
}

void TcpConnection::sendFromClientUI(const std::string &msg)
{
    boost::asio::write(clientSocket_, boost::asio::buffer(msg));
}

void TcpConnection::sendFromServerUI(const std::string &msg)
{
    boost::asio::write(serverSocket_, boost::asio::buffer(msg));
}