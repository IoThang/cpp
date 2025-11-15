//
// Created by tuo8hc on 10/21/25.
//

#ifndef EX01_EPOLL_H
#define EX01_EPOLL_H
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <sys/epoll.h>

#include "NetworkUtility.h"

namespace networking {
    using event_t = uint32_t;
    constexpr int MAX_EVENTS = 128;

    class Epoll {
    public:
        Epoll();
        ~Epoll() noexcept;

        Epoll(const Epoll &) = delete;
        Epoll& operator=(const Epoll &) = delete;

        Epoll(Epoll&&);
        Epoll& operator=(Epoll&&) noexcept;

        int get_fd() const;
        void add(int fd, event_t event, int user_data = 0);
        void modify(int fd, event_t event);
        void remove(int fd) noexcept;
        size_t wait(std::vector<epoll_event>& events, int timeout = -1);
    private:
        int epoll_fd_ = -1;
        void close();
    };
}


#endif //EX01_EPOLL_H