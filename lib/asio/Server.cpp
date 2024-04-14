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
    // auto socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    // // auto acceptor_ptr = std::make_shared<boost::asio::ip::tcp::acceptor>(io_context_, endpoint_);
    // acceptor_.async_accept(*socket_ptr, std::bind(&Server::accept_handler, this, socket_ptr, std::placeholders::_1));

    acceptor_.async_accept(socket_, [this](const boost::system::error_code &error)
                           {
            if (!error) {
                handle_connection();
            } else {
                std::cerr << "Accept error: " << error.message() << std::endl;
            } });
}

void Server::accept_handler(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection Succeeded\n";
        if (socket->is_open())
            std::cout << " OPEN\n";
        handle_connection();
        if (socket->is_open())
            std::cout << " OPEN\n";
    }
    else
    {
        std::cout << "ERROR: " << error.message();
    }
    // start_accept(); // recursively wait for new connection
}

void Server::handle_connection()
{
    std::cout << "Waiting to read\n";
    // boost::asio::async_read(*socket, boost::asio::buffer(data_, max_length_), std::bind(&Server::read_callback, this,socket, std::placeholders::_1, std::placeholders::_2));
    // boost::asio::async_read(*socket, boost::asio::buffer(data_, max_length_),
    //                         std::bind(&Server::read_callback, this, socket, std::placeholders::_1, std::placeholders::_2));
    char data[1024];
    size_t length = socket_.read_some(boost::asio::buffer(data));

    std::cout << "Received: " << std::string(data, length) << std::endl;

    // Close the socket
    socket_.close();
    start_accept();
}

// void Server::read_callback(std::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error, std::size_t length)
// {
//     if (socket->is_open())
//         std::cout << " areadOPEN\n";

//     if (!error)
//     {
//         if (length > 0)
//         {
//             std::cout << "Received data from client: " << std::string(data_, length) << std::endl;
//             // Do something with the received data

//             // Continue reading more data recursively
//             // boost::asio::async_read(*socket, boost::asio::buffer(data_, max_length_), std::bind(&Server::read_callback, this,socket, std::placeholders::_1, std::placeholders::_2));
//             Server::handle_connection(socket);
//         }
//         else
//         {
//             std::cout << data_ << "Client closed connection without sending data" << std::endl;
//             // Handle the case where the client closes the connection without sending any data
//             // Close the socket or take other appropriate action
//         }
//     }
//     else if (error == boost::asio::error::eof)
//     {
//         std::cout << "Connection closed by client" << std::endl;
//         // Handle EOF (End of File) condition
//         // Close the socket or take other appropriate action
//     }
//     else
//     {
//         std::cout << "Read Error: " << error.message() << std::endl;
//     }
// }

void Server::sendToClient(const std::string message)
{
    std::strncpy(data_, message.c_str(), max_length_);

    boost::asio::write(socket_, boost::asio::buffer(data_, max_length_));
}