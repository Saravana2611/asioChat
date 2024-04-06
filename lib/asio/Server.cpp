#include <Server.hpp>
#include <iostream>

Server::Server(boost::asio::io_context &io_context,
               const boost::asio::ip::tcp::endpoint &endpoint) : io_context_(io_context),
                                                                 acceptor_(io_context, endpoint), socket_(io_context_)
{
    std::cout << "CREATED SERVER\n";
    start_accept();
}

void Server::start_accept() //New connection
{
    acceptor_.async_accept(socket_, std::bind(&Server::accept_handler, this, std::placeholders::_1));
}

void Server::accept_handler(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection Succeded\n";
        // Do something read/write
    }
    start_accept(); //recursively wait for new connection
}