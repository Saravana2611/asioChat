#pragma once

#include "mediator.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

class AppManager : public Mediator {
private:
    Server *component1_;
    Client *component2_;

public:
    AppManager(Server *c1, Client *c2);
    void Notify(BaseComponent *sender, const std::string &event) const override;
};
