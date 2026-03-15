#pragma once

enum EventType
{
    PROTOCOL_SELECTED,
    FROM_SERVER_UI_TO_SERVER,
    FROM_CLIENT_UI_TO_CLIENT,
    FROM_SERVER_TO_SERVER_UI,
    FROM_CLIENT_TO_CLIENT_UI
};

class Message
{

public:
    enum EventType
    {
        PROTOCOL_SELECTED,
        FROM_SERVER_UI_TO_SERVER,
        FROM_CLIENT_UI_TO_CLIENT,
        FROM_SERVER_TO_SERVER_UI,
        FROM_CLIENT_TO_CLIENT_UI
    };
    Message() = default;
    Message(EventType eventType, const std::string &data)
    {
        this->eventType = eventType;
        this->data = data;
    }

    std::string data;
    EventType eventType;
};