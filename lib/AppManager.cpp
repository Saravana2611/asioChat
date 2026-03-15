#include "AppManager.hpp"
#include <iostream>

AppManager::AppManager(QtApp *qtApp, NetworkManager *NetworkManager) : qtApp_(qtApp), networkManager_(NetworkManager)
{
    this->qtApp_->set_mediator(this);
    this->networkManager_->set_mediator(this);
}

void AppManager::Notify(BaseComponent *sender, const Message& message) const
{
    if (message.eventType == Message::PROTOCOL_SELECTED)
    {
        std::cout << "Protocol selected: " << message.data << std::endl;
        networkManager_->startConnection(message.data);
    }
    else if (message.eventType == Message::FROM_SERVER_UI_TO_SERVER)
    {
        std::cout << "FROM_SERVER_UI_TO_SERVER with msg: " << message.data << std::endl;
        networkManager_->sendMessage(message);
    }
    else if (message.eventType == Message::FROM_CLIENT_UI_TO_CLIENT)
    {
        std::cout << "FROM_CLIENT_UI_TO_CLIENT with msg: " << message.data << std::endl;
        networkManager_->sendMessage(message);
    }
    else if (message.eventType == Message::FROM_SERVER_TO_SERVER_UI)
    {
        std::cout << "FROM_SERVER_TO_SERVER_UI with msg: " << message.data << std::endl;
        this->qtApp_->appendMsgToTextArea(message.data);
    }
    else if (message.eventType == Message::FROM_CLIENT_TO_CLIENT_UI)
    {
        std::cout << "FROM_CLIENT_TO_CLIENT_UI with msg: " << message.data << std::endl;
        this->qtApp_->appendMsgToTextArea2(message.data);
    }
}
