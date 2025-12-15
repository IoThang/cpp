//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_CLIENTINFO_H
#define EX01_CLIENTINFO_H
#include <chrono>
#include <set>
#include <string>
#include <iostream>
#include "IObserver.h"

namespace networking {
    class ClientInfo : public IObserver {
    public:
        explicit ClientInfo(int fd);
        ~ClientInfo() override = default;

        void update(RoomEvent ev, std::string room, std::string source) override;
        void setName(std::string name);
        std::string getName() const;
        std::string getRoomID() const;

        std::string name_;
        int fd_;
        std::string room_id_;
        std::chrono::steady_clock::time_point join_time_;
        std::chrono::steady_clock::time_point last_active_;
        size_t msg_count_{};
        // std::set<std::string> friends_list_;
    };
}



#endif //EX01_CLIENTINFO_H