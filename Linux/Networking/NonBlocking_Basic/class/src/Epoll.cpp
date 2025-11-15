//
// Created by tuo8hc on 10/17/25.
//

#include "../inc/Epoll.h"

#include <cstring>

Epoll::Epoll() {
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        std::cerr << "Failed to create epoll events" << std::endl;
        throw std::runtime_error("Failed to create epoll events");
    }
}

Epoll::~Epoll() {
    if (epoll_fd_ >= 0) {
        ::close(epoll_fd_);
    }
}


Epoll::Epoll(Epoll&& obj) noexcept {
    if (this != &obj) {
        epoll_fd_ = obj.epoll_fd_;
        ::close(epoll_fd_);
        obj.epoll_fd_ = -1;
    }
}

Epoll& Epoll::operator=(Epoll&& obj) noexcept {
    if (this != &obj) {
        epoll_fd_ = obj.epoll_fd_;
        ::close(epoll_fd_);
        obj.epoll_fd_ = -1;
    }
    return *this;
}

int Epoll::get() const {
    return epoll_fd_;
}

void Epoll::add(int fd, uint32_t events) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = events;

    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event) == -1) {
        throw std::runtime_error(std::string("Failed to add epoll events") + std::strerror(errno));
    }
}

void Epoll::remove(int fd) {
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        throw std::runtime_error(std::string("Failed to remove epoll events: ") + strerror(errno));
    }
}

void Epoll::modify(int fd, uint32_t events) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = events;
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event) == -1) {
        throw std::runtime_error(std::string("Failed to modify epoll events: ") + strerror(errno));
    }
}

int Epoll::wait(struct epoll_event* events, int maxevents, int timeout) {
    int num_events = epoll_wait(epoll_fd_, events, maxevents, timeout);
    if (num_events == -1) {
        throw std::runtime_error(std::string("Failed to wait for epoll events") + strerror(errno));
    }
    return num_events;
}