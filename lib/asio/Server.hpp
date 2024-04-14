#pragma once
#include <boost/asio.hpp>
#include "../BaseComponent.hpp"

class Server : public BaseComponent
{
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::endpoint endpoint_;
    const std::size_t max_length_ = 1024;
    char data_[1024];

public:
    Server(boost::asio::io_context &io_context,
           const boost::asio::ip::tcp::endpoint &endpoint);
    void start_accept();
    void accept_handler(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error);
    // void handle_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handle_connection();
    // void read_callback(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error, std::size_t length);
    void sendToClient(const std::string message);
};