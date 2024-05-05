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
    acceptor_.async_accept(socket_, std::bind(&Server::accept_handler, this, std::placeholders::_1));
}

void Server::accept_handler(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection Succeeded\n";
        handle_connection();
        start_accept(); // recursively wait for new connection
    }
    else if (error == boost::asio::error::already_open)
    {
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
    if (!error)
    {
        if (length > 0)
        {
            std::cout << "Received data from client: " << std::string(data_, length) << std::endl;
            if (std::string(data_) == "Server is running")
            {
                std::cout << "closing socket\n";
                strcpy(data_, "");
                socket_.close();
                start_accept();
            }
            else
            {
                this->mediator_->Notify(this, "B", data_);
                strcpy(data_, "");
                Server::handle_connection();
            }
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