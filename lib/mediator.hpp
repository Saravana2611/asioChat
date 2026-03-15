#pragma once
#include <string>
#include "Messages.hpp"

class BaseComponent; // Forward declaration

class Mediator
{
public:
    virtual void Notify(BaseComponent *sender, const Message& message) const = 0;
};
