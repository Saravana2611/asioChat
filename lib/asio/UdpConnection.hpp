#include "IConnection.hpp"

#include <string>
#include <boost/asio.hpp>

constexpr int UDP_PORT_CLIENT = 12345;
constexpr int UDP_PORT_SERVER = 12344;
const std::string UDP_IP = "127.0.0.1";

class UdpConnection : public IConnection
{
        boost::asio::ip::udp::socket clientSocket_;
        boost::asio::ip::udp::socket serverSocket_;
        boost::asio::ip::udp::endpoint clientEndpoint_;
        boost::asio::ip::udp::endpoint serverEndpoint_;
        const std::size_t max_length_ = 4096;
        std::array<char, 4096> serverBuffer_;
        std::array<char, 4096> clientBuffer_;
        MessageHandler onMessageReceived_;

    public:
        UdpConnection(boost::asio::io_context& io_context, MessageHandler onMessageReceived);
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