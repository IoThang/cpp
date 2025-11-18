//
// Created by TUO8HC on 10/10/2025.
//

#ifndef NETWORKING_MESSAGE_H
#define NETWORKING_MESSAGE_H
#include <chrono>
#include <string>

using namespace std::chrono;

enum class MessageType {
    CHAT = 0,
    BROADCAST = 1,
    DISCONNECT = 2,
    JOIN = 3
};

class Message {
public:
    Message(MessageType type, std::string const& data);

    std::string getMessageType() const;
    std::string getPayload() const;
    time_point<system_clock> getTimestamp() const;

private:
    MessageType type;
    std::string payload; // data
    time_point<system_clock> timestamp;
};

#endif //NETWORKING_MESSAGE_H