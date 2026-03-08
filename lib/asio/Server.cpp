#include <Server.hpp>
#include <iostream>

Server::Server(boost::asio::io_context &io_context,
               const boost::asio::ip::tcp::endpoint &endpoint) : io_context_(io_context), endpoint_(endpoint),
                                                                 acceptor_(io_context, endpoint), socket_(io_context_)
{
}

void Server::start_accept() // New connection
{
    std::cout << "Waiting for new connection\n";
    // only for the first connection. After that, the socket is already associated with the accepted connection,
    // which leads to error boost::asio::error::already_open
    acceptor_.async_accept(socket_, std::bind(&Server::accept_handler, this, std::placeholders::_1));
}

void Server::accept_handler(const boost::system::error_code &error)
{
    std::cout << "Inside accept_handler\n";
    if (!error)
    {
        std::cout << "Connection Succeeded\n";
        handle_connection();
        start_accept(); // recursively wait for new connection
    }
    else if (error == boost::asio::error::already_open)
    {
        std::cout << "ERROR: " << error.message();
    }
    else
    {
        std::cout << "ERROR: " << error.message();
    }
}

void Server::handle_connection()
{
    socket_.async_read_some(boost::asio::buffer(data_), std::bind(&Server::read_callback, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::read_callback(const boost::system::error_code &error, std::size_t length)
{
    if (not error)
    {
        if (length > 0)
        {
            this->mediator_->Notify(this, "SEND_TO_UI", data_);
            strcpy(data_, "");
            Server::handle_connection();
        }
        else
        {
            std::cout << data_ << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << data_ << "Connection closed by client" << std::endl;
        socket_.close();
    }
    else
    {
        std::cout << data_ << "Read Error: " << error.message() << std::endl;
    }
}

void Server::sendToClient(const std::string message)
{
    std::strncpy(data_, message.c_str(), max_length_);
    boost::asio::write(socket_, boost::asio::buffer(data_, max_length_));
}