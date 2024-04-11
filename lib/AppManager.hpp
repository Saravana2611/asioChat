#pragma once

#include "mediator.hpp"
#include "qt/QtApp.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

class AppManager : public Mediator
{
private:
    QtApp *component1_;
    Server *component2_;

public:
    AppManager(QtApp *c1, Server *c2);
    void Notify(BaseComponent *sender, const std::string &event, std::string message) const override;
};
