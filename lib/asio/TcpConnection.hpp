#include "IConnection.hpp"

#include <string>
#include <boost/asio.hpp>

constexpr int TCP_PORT = 12345;
const std::string TCP_IP = "127.0.0.1";

class TcpConnection : public IConnection
{
        boost::asio::ip::tcp::socket clientSocket_;
        boost::asio::ip::tcp::socket serverSocket_;
        boost::asio::ip::tcp::acceptor acceptor_;
        const std::size_t max_length_ = 4096;
        std::array<char, 4096> serverBuffer_;
        std::array<char, 4096> clientBuffer_;
        MessageHandler onMessageReceived_;

    public:
        TcpConnection(boost::asio::io_context& io_context, MessageHandler onMessageReceived);
        void accept_handler(const boost::system::error_code &error);
        void handleServerRead();
        void serverReadCallback(const boost::system::error_code &error, std::size_t msgLength);
        void startServer(int port) override;
        void connectClient(const std::string& host, int port) override;
        void handleClientRead();
        void clientReadCallback(const boost::system::error_code &error, std::size_t msgLength);

        void sendFromClientUI(const std::string& msg) override;
        void sendFromServerUI(const std::string& msg) override;
};