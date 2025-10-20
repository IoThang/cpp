//
// Created by tuo8hc on 10/17/25.
//

#ifndef EX01_EPOLL_H
#define EX01_EPOLL_H

#include <string.h>
#include <unistd.h>
#include <cstdint>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <iostream>

// === RAII Epoll Wrapper ===
class Epoll {
public:
    Epoll();
    ~Epoll();

    // Disable copy
    Epoll(Epoll const&) = delete;
    Epoll& operator=(Epoll const&) = delete;
    // Allow move
    Epoll(Epoll&&) noexcept;
    Epoll& operator = (Epoll&&) noexcept;

    int get() const;
    void add(int fd, uint32_t events);
    void remove(int fd);
    void modify(int fd, uint32_t events);
    int wait(struct epoll_event* events, int maxevents, int timeout);
private:
    int epoll_fd_;
};

#endif //EX01_EPOLL_H