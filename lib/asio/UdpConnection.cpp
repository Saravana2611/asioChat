#include <iostream>
#include <thread>

#include "UdpConnection.hpp"

UdpConnection::UdpConnection(
    boost::asio::io_context &io_context,
    MessageHandler onMessageReceived)
    : clientSocket_(io_context),
      serverSocket_(io_context),
      clientEndpoint_(boost::asio::ip::address_v4::loopback(), UDP_PORT_CLIENT),
      serverEndpoint_(boost::asio::ip::address_v4::loopback(), UDP_PORT_SERVER),
      onMessageReceived_(onMessageReceived)
{
    startServer(UDP_PORT_SERVER);
    connectClient(UDP_IP, UDP_PORT_CLIENT);
}

void UdpConnection::handleServerRead()
{
    boost::asio::ip::udp::endpoint remoteEndpoint;
    serverSocket_.async_receive_from(boost::asio::buffer(serverBuffer_), remoteEndpoint, std::bind(&UdpConnection::serverReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void UdpConnection::serverReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(serverBuffer_.data(), msgLength);
            Message message(Message::FROM_SERVER_TO_SERVER_UI, msg);
            onMessageReceived_(message);
            UdpConnection::handleServerRead();
        }
        else
        {
            std::cout << serverBuffer_.data() << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << serverBuffer_.data() << "Connection closed by client" << std::endl;
        serverSocket_.close();
    }
    else
    {
        std::cout << serverBuffer_.data() << "Read Error: " << error.message() << std::endl;
    }
}

void UdpConnection::startServer(int port)
{
    std::cout << "Starting UDP server on port " << port << std::endl;

    serverSocket_.open(serverEndpoint_.protocol());
    serverSocket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    serverSocket_.bind(serverEndpoint_);

    std::cout << "Waiting for data from client" << std::endl;
    handleServerRead();
}

void UdpConnection::connectClient(const std::string &host, int port)
{
    std::cout << "Connecting to UDP server at " << host << ":" << port << std::endl;

    clientSocket_.open(clientEndpoint_.protocol());
    clientSocket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    clientSocket_.bind(clientEndpoint_);
    handleClientRead();
}

void UdpConnection::handleClientRead()
{
    boost::asio::ip::udp::endpoint remoteEndpoint;
    clientSocket_.async_receive_from(boost::asio::buffer(clientBuffer_), remoteEndpoint,
        std::bind(&UdpConnection::clientReadCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void UdpConnection::clientReadCallback(const boost::system::error_code &error, std::size_t msgLength)
{
    if (not error)
    {
        if (msgLength > 0)
        {
            std::string msg(clientBuffer_.data(), msgLength);
            Message message(Message::FROM_CLIENT_TO_CLIENT_UI, msg);
            onMessageReceived_(message);
            UdpConnection::handleClientRead();
        }
        else
        {
            std::cout << clientBuffer_.data() << "Client closed connection without sending data" << std::endl;
        }
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << clientBuffer_.data() << "Connection closed by client" << std::endl;
        clientSocket_.close();
    }
    else
    {
        std::cout << clientBuffer_.data() << "Read Error: " << error.message() << std::endl;
    }
}

void UdpConnection::sendFromClientUI(const std::string &msg)
{
    const size_t noOfFragments = 5;
    const size_t totalSize = msg.size();
    const size_t baseFragmentSize = (totalSize + noOfFragments - 1) / noOfFragments;

    for (size_t i = 0; i < totalSize; i += baseFragmentSize)
    {
        std::string fragment = msg.substr(i, baseFragmentSize);
        clientSocket_.send_to(boost::asio::buffer(fragment), serverEndpoint_);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void UdpConnection::sendFromServerUI(const std::string &msg)
{
    serverSocket_.send_to(boost::asio::buffer(msg), clientEndpoint_);
}