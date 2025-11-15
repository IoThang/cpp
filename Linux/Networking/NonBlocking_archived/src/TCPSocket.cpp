//
// Created by tuo8hc on 10/14/25.
//

#include "../inc/TCPSocket.h"

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

TCPSocket::TCPSocket() : sock_fd_(-1) {
}

TCPSocket::~TCPSocket() {
    if (sock_fd_ >= 0) {
        ::close(sock_fd_);
    }
}

int TCPSocket::create() {
    sock_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd_ < 0) {
        throw std::runtime_error("[TCPSocket::create] Failed to create socket");
    }
    std::cout << "[TCPSocket::create] sock_fd_ : " << sock_fd_ << std::endl;
    return sock_fd_;
}

void TCPSocket::set_fd(int const fd) {
    sock_fd_ = fd;
}

int TCPSocket::get_fd() const {
    return sock_fd_;
}

int TCPSocket::bind(int const port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    return ::bind(sock_fd_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
}

int TCPSocket::listen(int const backlog) {
    return ::listen(sock_fd_, backlog);
}

int TCPSocket::accept(sockaddr_in& client_addr, socklen_t& addr_len) {
    return ::accept(sock_fd_, reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
}

int TCPSocket::connect(const std::string& host, int const port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("[TCPSocket::connect] Failed to convert IP address");
    }

    return ::connect(sock_fd_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
}

int TCPSocket::send(std::string const &msg) {
    return ::send(sock_fd_, const_cast<char*>(msg.c_str()), msg.size(), 0);
}

int TCPSocket::recv(std::string &buf) {
    char buffer[1024];
    int len = ::recv(sock_fd_, buffer, sizeof(buffer) - 1, 0);
    if (len > 0) {
        buffer[len] = '\0';
        buf.assign(buffer, len);
        return len;
    }
    return len;
}

void TCPSocket::close() {
    if (sock_fd_ >= 0) {
        ::close(sock_fd_);
        sock_fd_ = -1;
    }
}

void TCPSocket::set_non_blocking(bool const enable) {
    int flag = fcntl(sock_fd_, F_GETFL, 0);
    if (enable) {
        flag |= O_NONBLOCK;
    }
    else {
        flag &= ~O_NONBLOCK;
    }
    if (fcntl(sock_fd_, F_SETFL, flag) < 0) {
        throw std::runtime_error("[TCPSocket::set_non_blocking] Failed to set non-blocking");
    }
}
