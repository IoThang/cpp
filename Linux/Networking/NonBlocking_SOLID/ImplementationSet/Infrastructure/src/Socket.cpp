//
// Created by tuo8hc on 10/21/25.
//

#include "../inc/Socket.h"


networking::Socket::Socket(int fd) : fd_(fd) {
    if (fd_ >= 0) {
        NetworkUtility::setNonBlocking(fd_);
        NetworkUtility::setSockOpt(fd_, SO_REUSEADDR | SO_REUSEPORT);
    }
}

networking::Socket::Socket(int domain, int type, int protocol) {
    fd_ = NetworkUtility::createSocket(domain, type, protocol);
    if (fd_ > 0) {
        NetworkUtility::setNonBlocking(fd_);
    }
}

networking::Socket::Socket(Socket&& other) {
    if (this != &other) {
        Socket::close();
        fd_ = other.fd_;
        other.fd_ = -1;
    }
}

networking::Socket& networking::Socket::operator=(Socket&& other) noexcept {
    if (this != &other) {
        Socket::close();
        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}

int networking::Socket::get_fd() const noexcept {
    return fd_;
}

void networking::Socket::bindAndListen(port_type port, int backlog) {
    if (fd_ == -1) {
        throw std::runtime_error("[ERROR] networking::Socket::bindAndListen(): socket not available" + std::to_string(errno));
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    NetworkUtility::bind(fd_, reinterpret_cast<sockaddr_in*> (&addr), (socklen_t) sizeof(addr));
    NetworkUtility::listen(fd_, backlog);
}

void networking::Socket::connectTo(std::string &host, port_type port) {
    if (fd_ == -1) {
        throw std::runtime_error("[ERROR] networking::Socket::connectTo(): socket not available" + std::to_string(errno));
    }
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("[ERROR] networking::Socket::connectTo(): invalid ip address" + std::to_string(errno));
    }
    NetworkUtility::connect(fd_, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr));
}

networking::Socket networking::Socket::accept() {
    return Socket(NetworkUtility::accept(fd_));
}

void networking::Socket::close() noexcept {
    if (fd_ >= 0) {
        NetworkUtility::close(fd_);
        fd_ = -1;
    }
}
