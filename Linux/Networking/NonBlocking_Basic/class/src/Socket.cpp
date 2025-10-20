//
// Created by tuo8hc on 10/17/25.
//

#include "../inc/Socket.h"

#include <unistd.h>

Socket::Socket() : sock_fd_(-1) {}
Socket::~Socket() noexcept {
    if (sock_fd_ >= 0) {
        ::close(sock_fd_);
        sock_fd_ = -1;
    }
}

Socket::Socket(Socket&& obj) noexcept {
    if (this != &obj) {
        ::close(sock_fd_);
        sock_fd_ = obj.sock_fd_;
        obj.sock_fd_ = -1;
    }
}

Socket& Socket::operator = (Socket&& obj) noexcept {
    if (this != &obj) {
        ::close(sock_fd_);
        sock_fd_ = obj.sock_fd_;
        obj.sock_fd_ = -1;
    }
    return *this;
}

bool Socket::valid() const {
    return sock_fd_ >= 0;
}

int Socket::get() const {
    return sock_fd_;
}

void Socket::close() noexcept {
    ::close(sock_fd_);
}

int Socket::release() {
    int temp = sock_fd_;
    sock_fd_ = -1;
    return temp;
}
