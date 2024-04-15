#include "AppManager.hpp"
#include <iostream>

AppManager::AppManager(QtApp *c1, Server *c2) : qtApp_(c1), server_(c2)
{
    this->qtApp_->set_mediator(this);
    this->server_->set_mediator(this);
    isServer_ = true;
}

AppManager::AppManager(QtApp *c1, Client *c2) : qtApp_(c1), client_(c2)
{
    this->qtApp_->set_mediator(this);
    this->client_->set_mediator(this);
    isServer_ = false;
}

void AppManager::Notify(BaseComponent *sender, const std::string &event, std::string message) const
{
    if (event == "A")
    {
        std::cout << "Mediator reacts on A and triggers following operations: " << message << std::endl;
        if (isServer_)
        {
            this->server_->sendToClient(message);
        }
        else
        {
            this->client_->sendToClient(message);
        }
    }
    if (event == "D")
    {
        std::cout << "Mediator reacts on D and triggers following operations:\n";
        // this->component1_->DoB();
        // this->component2_->DoC();
    }
}
