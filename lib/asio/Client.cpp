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
    start_client();
}

void Client::start_client()
{
    try
    {
        std::cout << "Connecting to Server...\n";
        // socket_.connect(endpoint_);
        auto socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        (socket_ptr)->connect(endpoint_);
        std::cout<<"Connected\n";
        handle_connection(socket_ptr);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}
void Client::handle_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    std::string message = "Hello world 1";

    // boost::asio::async_write(*socket, boost::asio::buffer(message), std::bind(&Client::read_callback, this, socket,std::placeholders::_1, std::placeholders::_2));
    // socket->write_some(boost::asio::buffer(message));
    std::cout << message;
    boost::asio::write(*socket, boost::asio::buffer(message));
    std::this_thread::sleep_for(std::chrono::seconds(4));
    
    message = "Hello world 2";
    std::cout << message;
    boost::asio::write(*socket, boost::asio::buffer(message));
    std::cout << "Data Sent\n";
    // boost::asio::async_read(*socket, boost::asio::buffer(data_, max_length_), std::bind(&Client::read_callback, this, socket,  std::placeholders::_1, std::placeholders::_2));
}

void Client::read_callback(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error, std::size_t length)
{
    if (!error)
    {
        std::cout << "Received data from client: " << data_ << std::endl;
        // Do something with the received data

        // Continue reading more data recursively
    }
    else
    {
        std::cout << "Error during async_read"  << error.message() << std::endl;
    }
            handle_connection(socket);
}

Client::~Client()
{
    std::cout<<"Client destroyed\n";
}