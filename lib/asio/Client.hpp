#pragma once
#include <boost/asio.hpp>
#include "../BaseComponent.hpp"

class Client : public BaseComponent
{
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::endpoint endpoint_;
    const std::size_t max_length_ = 1024;
    char data_[1024];

public:
    Client(boost::asio::io_context &io_context,
           const boost::asio::ip::tcp::endpoint &endpoint);
    void start_client();
    void handle_connection();
    void read_callback(const boost::system::error_code &error, std::size_t length);
};