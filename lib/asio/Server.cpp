#include <Server.hpp>
#include <iostream>

Server::Server(boost::asio::io_context &io_context,
               const boost::asio::ip::tcp::endpoint &endpoint) : io_context_(io_context),
                                                                 acceptor_(io_context, endpoint), socket_(io_context_)
{
    std::cout << "CREATED SERVER\n";
    start_accept();
}

void Server::start_accept() // New connection
{
    acceptor_.async_accept(socket_, std::bind(&Server::accept_handler, this, std::placeholders::_1));
}

void Server::accept_handler(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection Succeded\n";
        handle_connection();
        start_accept(); // recursively wait for new connection
    }
}

void Server::handle_connection()
{
    std::cout << "Waiting to read\n";
    boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length_), std::bind(&Server::read_callback, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::read_callback(const boost::system::error_code &error, std::size_t length)
{
    if (!error)
    {
        std::cout << "Received data from client: " << data_ << std::endl;
        // Do something with the received data

        // Continue reading more data recursively
        Server::handle_connection();
    }
}

void Server::sendToClient(const std::string message)
{
    std::strncpy(data_, message.c_str(), max_length_);

    boost::asio::write(socket_, boost::asio::buffer(data_, max_length_));
}