#pragma once
#include "mediator.hpp"

class Mediator; // Forward declaration

class BaseComponent {
protected:
    Mediator *mediator_;

public:
    // Constructor with default argument
    BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {}

    // Setter for mediator
    void set_mediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }
};
