//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_SERVERHANDLER_H
#define EX01_SERVERHANDLER_H
#include <memory>
#include <unordered_map>
#include <iostream>
#include "Epoll.h"
#include "IEventHandler.h"

namespace networking {
    class ServerHandler : public IEventHandler{
    public:
        explicit ServerHandler(Epoll& epoll, std::unordered_map<int, std::unique_ptr<IEventHandler>>& clients, int server_fd);

        void handle(int fd, event_t events) override;
    private:
        Epoll& epoll_;
        std::unordered_map<int, std::unique_ptr<IEventHandler>>& client_handlers_;
        int server_fd_;
    };
}



#endif //EX01_SERVERHANDLER_H