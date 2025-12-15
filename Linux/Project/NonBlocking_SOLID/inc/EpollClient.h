//
// Created by tuo8hc on 10/24/25.
//

#ifndef EX01_EPOLLCLIENT_H
#define EX01_EPOLLCLIENT_H
#include <memory>

#include "Socket.h"
#include "Epoll.h"
#include "IEventHandler.h"
#include "ClientSocketHandler.h"

namespace networking {
    class EpollClient {
    public:
        explicit EpollClient(std::string host, port_type port);
        void run();
    private:
        std::string host_;
        port_type port_;
        Socket socket_;
        Epoll epoll_;
        std::unique_ptr<IEventHandler> socket_handler_;
        std::unique_ptr<IEventHandler> stdin_handler_;
    };
}

#endif //EX01_EPOLLCLIENT_H