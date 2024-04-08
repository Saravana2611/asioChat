#include "AppManager.hpp"
#include <iostream>

AppManager::AppManager(Server *c1, Client *c2) : component1_(c1), component2_(c2) {
    this->component1_->set_mediator(this);
    this->component2_->set_mediator(this);
}

void AppManager::Notify(BaseComponent *sender, const std::string &event) const {
    if (event == "A") {
        std::cout << "Mediator reacts on A and triggers following operations:\n";
        // this->component2_->DoC();
    }
    if (event == "D") {
        std::cout << "Mediator reacts on D and triggers following operations:\n";
        // this->component1_->DoB();
        // this->component2_->DoC();
    }
}
