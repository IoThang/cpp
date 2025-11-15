//
// Created by tuo8hc on 10/11/25.
//

#include "../inc/TCPSocket.h"

#include <memory>
#include <unistd.h>

TCPSocket::TCPSocket() : socket_(-1) {
}

TCPSocket::~TCPSocket() {
    if (socket_ >= 0) {
        ::close(socket_);
    }
}

int TCPSocket::create() {
    socket_ = ::socket(PF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }
    return socket_;
}

int TCPSocket::get_fd() const {
    return socket_;
}

int TCPSocket::bind(int port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(port));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    return ::bind(socket_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
}

int TCPSocket::listen(int backlog) {
    return ::listen(socket_, backlog);
}

int TCPSocket::accept(sockaddr_in& client_addr, socklen_t& addr_len) {
    return ::accept(socket_, reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
}

int TCPSocket::connect(const std::string& host, int port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(port));
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address");
    }
    return ::connect(socket_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
}

int TCPSocket::send(std::string const& buf) {
    return ::send(socket_, buf.c_str(), static_cast<int>(buf.length()), 0);
}

int TCPSocket::recv(std::string &buf) {
    char buffer[1024];
    int len = ::recv(socket_, buffer, sizeof(buffer) - 1, 0);
    if (len > 0) {
        buffer[len] = '\0';
        buf.assign(buffer, len);
        return len;
    }
    return len;
}

void TCPSocket::close() {
    if (socket_ >= 0) {
        ::close(socket_);
        socket_ = -1;
    }
}
