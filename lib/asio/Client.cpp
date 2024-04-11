#include <Client.hpp>
#include <iostream>
#include <cstring>

Client::Client(boost::asio::io_context &io_context,
               const boost::asio::ip::tcp::endpoint &endpoint) : io_context_(io_context), endpoint_(endpoint),
                                                                 acceptor_(io_context, endpoint),
                                                                 socket_(io_context_)
{
    std::cout << "CREATED Client\n";
    start_client();
}

void Client::start_client()
{
    try
    {
        socket_.connect(endpoint_);
        std::cout << "Connected to server\n";

        handle_connection();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}
void Client::handle_connection()
{
    boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length_), std::bind(&Client::read_callback, this, std::placeholders::_1, std::placeholders::_2));
}

void Client::read_callback(const boost::system::error_code &error, std::size_t length)
{
    if (!error)
    {
        std::cout << "Received data from client: " << data_ << std::endl;
        // Do something with the received data

        // Continue reading more data recursively
        Client::handle_connection();
    }
}