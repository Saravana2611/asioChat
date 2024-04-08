#pragma once
#include <string>

class BaseComponent; // Forward declaration

class Mediator {
public:
    virtual void Notify(BaseComponent *sender, const std::string &event) const = 0;
};
