#pragma once

#include "mediator.hpp"
#include "qt/QtApp.hpp"
#include "asio/NetworkManager.hpp"
#include "Messages.hpp"

class AppManager : public Mediator
{
private:
    QtApp *qtApp_ = nullptr;
    NetworkManager *networkManager_ = nullptr;    

public:
    AppManager(QtApp *c1, NetworkManager *c2);
    void Notify(BaseComponent *sender, const Message& message) const override;
};
