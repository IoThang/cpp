//
// Created by tuo8hc on 10/21/25.
//

#include "../inc/Epoll.h"

#include <unistd.h>



networking::Epoll::Epoll() : epoll_fd_(epoll_create1(EPOLL_CLOEXEC)) {
    if (epoll_fd_ < 0) {
        throw std::runtime_error("[ERROR] Failed to create epoll file descriptor" + std::to_string(errno));
    }
}

networking::Epoll::Epoll(Epoll&& other) {
    if (this != &other) {
        ::close(epoll_fd_);
        epoll_fd_ = other.epoll_fd_;
        other.epoll_fd_ = -1;
    }
}

networking::Epoll& networking::Epoll::operator=(Epoll&& other)  noexcept {
    if (this != &other) {
        ::close(epoll_fd_);
        epoll_fd_ = other.epoll_fd_;
        other.epoll_fd_ = -1;
    }
    return *this;
}

networking::Epoll::~Epoll() noexcept {
    close();
}

int networking::Epoll::get_fd() const {
    return epoll_fd_;
}

void networking::Epoll::close() {
    if (epoll_fd_ >= 0) {
        NetworkUtility::close(epoll_fd_);
        epoll_fd_ = -1;
    }
}

void networking::Epoll::add(int fd, event_t event, int user_data) {
    struct epoll_event ep_event;
    ep_event.events = event;
    ep_event.data.fd = (user_data != 0) ? user_data : fd;

    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ep_event) < 0) {
        throw std::runtime_error("[ERROR] Failed to add epoll file descriptor" + std::to_string(errno));
    }
}

void networking::Epoll::modify(int fd, event_t event) {
    struct epoll_event ep_event;
    ep_event.events = event;
    ep_event.data.fd = fd;

    if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ep_event) < 0) {
        throw std::runtime_error("[ERROR] Failed to modify epoll file descriptor" + std::to_string(errno));
    }
}

void networking::Epoll::remove(int fd) {
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL) < 0) {
        throw std::runtime_error("[ERROR] Failed to delete epoll file descriptor" + std::to_string(errno));
    }
}

size_t networking::Epoll::wait(std::vector<epoll_event>& events, int timeout) {
    int num = epoll_wait(epoll_fd_, events.data(), events.size(), timeout);
    if (num < 0) {
        throw std::runtime_error("[ERROR] Failed to wait epoll file descriptor" + std::to_string(errno));
    }
    return static_cast<size_t>(num);
}
