//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_SERVERSTDINHANDLER_H
#define EX01_SERVERSTDINHANDLER_H
#include <memory>
#include <unordered_map>
#include <iostream>
#include "Epoll.h"
#include "IEventHandler.h"
#include "ThreadPool.h"

namespace networking {
    class ServerStdinHandler : public IEventHandler {
    public:
        ServerStdinHandler(Epoll& epoll, std::unordered_map<int, std::unique_ptr<IEventHandler>>& clients, ThreadPool& threadPool);
        void handle(int fd, event_t events) override;
    private:
        std::unordered_map<int, std::unique_ptr<IEventHandler>>& client_handlers_;
        Epoll& epoll_;
        ThreadPool& pool_;
    };
}

#endif //EX01_SERVERSTDINHANDLER_H