#include <Client.hpp>
#include <iostream>

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

        // Do something with the connected socket, e.g., send/receive data
    }
    catch (const std::exception &e)
    {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}