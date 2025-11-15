//
// Created by tuo8hc on 10/24/25.
//

#ifndef EX01_CLIENTSOCKETHANDLER_H
#define EX01_CLIENTSOCKETHANDLER_H
#include "IEventHandler.h"
#include "NetworkUtility.h"
#include <sys/epoll.h>
#include <iostream>
namespace networking {
    class ClientSocketHandler : public IEventHandler {
    public:
        void handle(int fd, networking::event_t events) override;
    };
}



#endif //EX01_CLIENTSOCKETHANDLER_H