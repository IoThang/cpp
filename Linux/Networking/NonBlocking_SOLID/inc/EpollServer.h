//
// Created by tuo8hc on 10/23/25.
//

#ifndef EX01_EPOLLSERVER_H
#define EX01_EPOLLSERVER_H
#include <memory>
#include <unordered_map>

#include "Socket.h"
#include "Epoll.h"
#include "IEventHandler.h"
#include "../inc/ServerHandler.h"
#include "../inc/ServerStdinHandler.h"

namespace networking {
    class EpollServer {
    public:
        explicit EpollServer(int port);
        void run();
    private:
        int port_;
        Socket server_socket_;
        Epoll epoll_;
        std::unordered_map<int, std::unique_ptr<networking::IEventHandler>> client_handlers_;
        std::unique_ptr<IEventHandler> server_handler_;
        std::unique_ptr<IEventHandler> stdin_handler_;

        void cleanupFd(int fd);
    };
}

#endif //EX01_EPOLLSERVER_H