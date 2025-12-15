//
// Created by tuo8hc on 11/6/25.
//

#include "../../../inc/ClientInfo.h"

networking::ClientInfo::ClientInfo(int fd) : fd_(fd), join_time_(std::chrono::steady_clock::now()), last_active_(join_time_)
{
}

void networking::ClientInfo::update(RoomEvent ev, std::string room, std::string source) {
    switch (ev) {
        case RoomEvent::JOIN: {
            break;
        }
        case RoomEvent::LEAVE: {
            break;
        }
        case RoomEvent::MESSAGE: {
            break;
        }
        default: {
            std::cout << "[ClientInfo]: Invalid event" << std::endl;
        }
    }
}

void networking::ClientInfo::setName(std::string name) {
    name_ = std::move(name);
}

std::string networking::ClientInfo::getName() const {
    return name_;
}

std::string networking::ClientInfo::getRoomID() const {
    return getName();
}