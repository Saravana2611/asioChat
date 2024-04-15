#pragma once

#include "mediator.hpp"
#include "qt/QtApp.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

class AppManager : public Mediator
{
private:
    QtApp *qtApp_;
    Server *server_ = nullptr;
    Client *client_ = nullptr;
    bool isServer_;

public:
    AppManager(QtApp *c1, Server *c2);
    AppManager(QtApp *c1, Client *c2);
    void Notify(BaseComponent *sender, const std::string &event, std::string message) const override;
};
