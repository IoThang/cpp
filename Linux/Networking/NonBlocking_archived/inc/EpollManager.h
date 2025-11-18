//
// Created by tuo8hc on 10/14/25.
//

#ifndef EX01_EPOLLMANAGER_H
#define EX01_EPOLLMANAGER_H
#include <memory>
#include <unordered_map>

#include "IEventHandler.h"


class EpollManager {
public:
    EpollManager();
    ~EpollManager();

    void add_fd(int fd, uint32_t events, std::unique_ptr<IEventHandler> handler);
    void remove_fd(uint32_t fd);
    void update(int fd, uint32_t events);
    void wait_and_notify(int timeout_ms = -1);
private:
    int epoll_fd_;
    std::unordered_map<int, std::unique_ptr<IEventHandler>> handlers_;
};


#endif //EX01_EPOLLMANAGER_H