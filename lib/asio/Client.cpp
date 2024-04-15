#include <Client.hpp>
#include <iostream>
#include <thread>
#include <cstring>

Client::Client(boost::asio::io_context &io_context,
               const boost::asio::ip::tcp::endpoint &endpoint) : io_context_(io_context), endpoint_(endpoint),
                                                                 acceptor_(io_context, endpoint),
                                                                 socket_(io_context_)
{
    std::cout << "CREATED Client\n";
}

void Client::start_client()
{
    try
    {
        std::cout << "Connecting to Server...\n";
        socket_.connect(endpoint_);
        handle_connection();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}
void Client::handle_connection()
{
    socket_.async_read_some(boost::asio::buffer(data_), std::bind(&Client::read_callback, this, std::placeholders::_1, std::placeholders::_2));
}

void Client::read_callback(const boost::system::error_code &error, std::size_t length)
{
    if (!error)
    {
        std::cout << "Received data from client: " << data_ << std::endl;
        handle_connection();
    }
    else
    {
        std::cout << "Error during async_read"  << error.message() << std::endl;
    }
}

void Client::sendToClient(const std::string message)
{
    std::strncpy(data_, message.c_str(), max_length_);
    std::cout << "Sending this message " <<data_;
    boost::asio::write(socket_, boost::asio::buffer(data_, max_length_));
}

Client::~Client()
{
    std::cout<<"Client destroyed\n";
}