#pragma once

#include "../Messages.hpp"
#include <functional>

class IConnection
{
public:
    using MessageHandler =
        std::function<void(const Message&)>;

    virtual ~IConnection() = default;
    
    virtual void startServer(int port) = 0;
    virtual void connectClient(const std::string& host, int port) = 0;

    virtual void sendFromClientUI(const std::string& msg) = 0;
    virtual void sendFromServerUI(const std::string& msg) = 0;
};