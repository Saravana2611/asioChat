#pragma once
#include <boost/asio.hpp>

class Server
{
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

public:
    Server(boost::asio::io_context &io_context,
           const boost::asio::ip::tcp::endpoint &endpoint);
    void start_accept();
    void accept_handler(const boost::system::error_code &error);
};