//
// Created by tuo8hc on 10/24/25.
//

#ifndef EX01_CLIENTSTDINHANDLER_H
#define EX01_CLIENTSTDINHANDLER_H
#include "IEventHandler.h"
#include "Epoll.h"
#include "NetworkUtility.h"
#include "ThreadPool.h"

#include <string>

namespace networking {
    class ClientStdinHandler : public IEventHandler{
    public:
        explicit ClientStdinHandler(int fd);
        void handle(int fd, event_t events) override;

        void enterName(int socket_fd);
        void enterRoom(int socket_fd);
    private:
        int socket_fd_{};
        //  This flags below are to check the register and the room
        bool isRegistered_;
        bool isRoomSet_;
    };
}

#endif //EX01_CLIENTSTDINHANDLER_H