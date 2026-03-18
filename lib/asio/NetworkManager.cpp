#include <NetworkManager.hpp>
#include <TcpConnection.hpp>
#include <UdpConnection.hpp>
#include <TlsConnection.hpp>

NetworkManager::NetworkManager(boost::asio::io_context &io_context) : io_context_(io_context)
{
}

void NetworkManager::startConnection(const std::string &protocol)
{
    if (protocol == "tcp")
    {
        // start tcp server
        connection_ = std::make_unique<TcpConnection>(io_context_, [this](const Message &message)
                                                      { this->mediator_->Notify(this, message); });
    }
    else if (protocol == "udp")
    {
        // start udp server
        connection_ = std::make_unique<UdpConnection>(io_context_, [this](const Message &message)
                                                      { this->mediator_->Notify(this, message); });
    }
    else if (protocol == "tcp with tls")
    {
        // start tcp with tls server
        connection_ = std::make_unique<TlsConnection>(io_context_, [this](const Message &message)
                                                      { this->mediator_->Notify(this, message); });
    }
}

void NetworkManager::sendMessage(const Message &message)
{
    if (connection_)
    {
        if (message.eventType == Message::FROM_SERVER_UI_TO_SERVER)
        {
            connection_->sendFromServerUI(message.data);
        }
        else if (message.eventType == Message::FROM_CLIENT_UI_TO_CLIENT)
        {
            connection_->sendFromClientUI(message.data);
        }
    }
}
