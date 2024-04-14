#include <iostream>
#include <thread>
#include "utils.hpp"

void write_handler(const boost::system::error_code &error,
                   std::size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Data sent successfully" << std::endl;
    }
    else
    {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}
bool isServerRunning(boost::asio::io_context &io_context, boost::asio::ip::tcp::endpoint endpoint)
{
    auto socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
    try
    {
        socket_ptr->connect(endpoint);
        if (socket_ptr->is_open())
            std::cout << " OPEN\n";
        std::cout << "Connect is success\n";
        // boost::asio::write(*socket_ptr, boost::asio::buffer("HELLO"));
        boost::asio::async_write(*socket_ptr, boost::asio::buffer("HELLO"),
                                 std::bind(write_handler, std::placeholders::_1, std::placeholders::_2));
        if (socket_ptr->is_open())
            std::cout << " OPEN\n";
        std::this_thread::sleep_for(std::chrono::seconds(4));
        boost::asio::write(*socket_ptr, boost::asio::buffer("World"));
        if (socket_ptr->is_open())
            std::cout << " OPEN\n";
            
        socket_ptr->close();
        std::cout << " CLOSED OPEN\n";
        return true; // Connection succeeded, server is running
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Error connecting to server: " << e.what() << std::endl;
        return false; // Connection failed, server is not running or unreachable
    }
}
