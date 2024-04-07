#include "AppManager.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

#include <iostream>
#include <string>

BaseComponent::BaseComponent(Mediator *mediator) : mediator_(mediator)
{
}

void BaseComponent::set_mediator(Mediator *mediator)
{
  this->mediator_ = mediator;
}

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator
{
private:
  Server *server_;
  Client *client_;

public:
  ConcreteMediator(Server *c1, Client *c2) : server_(c1), client_(c2)
  {
    this->server_->set_mediator(this);
    // this->client_->set_mediator(this);
  }
  void Notify(BaseComponent *sender, std::string event) const override
  {
    if (event == "A")
    {
      std::cout << "Mediator reacts on A and triggers following operations:\n";
      //   this->client_->DoC();
    }
    if (event == "D")
    {
      std::cout << "Mediator reacts on D and triggers following operations:\n";
      //   this->server_->DoB();
      //   this->client_->DoC();
    }
  }
};
