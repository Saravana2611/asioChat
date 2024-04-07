#pragma once
#include <iostream>
#include <string>

/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class BaseComponent;
class Mediator
{
public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */

class BaseComponent
{
    Mediator *mediator_;

public:
    BaseComponent(Mediator *mediator = nullptr);
    void set_mediator(Mediator *mediator);
};