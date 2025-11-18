//
// Created by tuo8hc on 10/24/25.
//

#ifndef EX01_CLIENTSTDINHANDLER_H
#define EX01_CLIENTSTDINHANDLER_H
#include "IEventHandler.h"
#include "Epoll.h"
#include "NetworkUtility.h"

namespace networking {
    class ClientStdinHandler : public IEventHandler{
    public:
        explicit ClientStdinHandler(int fd);
        void handle(int fd, event_t events) override;
    private:
        int socket_fd_{};
    };
}

#endif //EX01_CLIENTSTDINHANDLER_H