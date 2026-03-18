#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>

#include <IConnection.hpp>

constexpr int TLS_TCP_PORT = 12345;
const std::string TLS_TCP_IP = "127.0.0.1";

class TlsConnection : public IConnection
{
    boost::asio::ip::tcp::socket clientSocket_;
    boost::asio::ip::tcp::socket serverSocket_;
    boost::asio::ip::tcp::acceptor acceptor_;
    const std::size_t max_length_ = 4096;
    std::array<char, 4096> serverBuffer_;
    std::array<char, 4096> clientBuffer_;
        
    boost::asio::ssl::context sslServerContext_;
    boost::asio::ssl::context sslClientContext_;

    std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> sslServerStream_;
    std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> sslClientStream_;

    bool serverVerified_ = false;
    bool clientVerified_ = false;

    MessageHandler onMessageReceived_;

public:
    TlsConnection(boost::asio::io_context &io_context, MessageHandler onMessageReceived);

    void startServer(int port);
    void connectClient(const std::string &host, int port);

    void handleServerRead();
    void serverReadCallback(const boost::system::error_code &error, std::size_t msgLength);

    void handleClientRead();
    void clientReadCallback(const boost::system::error_code &error, std::size_t msgLength);

    void sendFromClientUI(const std::string &msg);
    void sendFromServerUI(const std::string &msg);
};