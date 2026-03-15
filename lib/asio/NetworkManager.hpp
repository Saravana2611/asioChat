#pragma once

#include <boost/asio.hpp>

#include "../BaseComponent.hpp"
#include "../Messages.hpp"
#include "IConnection.hpp"

class NetworkManager : public BaseComponent
{
        boost::asio::io_context& io_context_;
        std::unique_ptr<IConnection> connection_;
    public:
        NetworkManager(boost::asio::io_context& io_context);
        void startConnection(const std::string& protocol);
        void sendMessage(const Message& message);
};