//
// Created by tuo8hc on 10/21/25.
//

#ifndef EX01_NETWORKUTILITY_H
#define EX01_NETWORKUTILITY_H
#include <fcntl.h>
#include <stdexcept>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

namespace networking {
    class NetworkUtility {
    public:
        static void setNonBlocking(int fd);
        static int createSocket(int domain, int type, int protocol);
        static void bind(int sock, const sockaddr_in* addr, socklen_t len);
        static void listen(int sock, int backlog);
        static int accept(int sock, sockaddr* addr = nullptr, socklen_t* addrlen = nullptr);
        static int connect(int sock, const sockaddr* addr, socklen_t len);
        static ssize_t read(int fd, void* buffer, size_t count);
        static ssize_t write(int fd, void* buffer, size_t count);
        static void close(int fd) noexcept;

    };
}  // namespace networking

inline void networking::NetworkUtility::setNonBlocking(int fd) {
    //  Check flag
    int flag = fcntl(fd, F_GETFL);
    if (flag < 0) {
        throw std::runtime_error("[ERROR]: Get flag failed" + std::to_string(errno));
    }
    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) < 0) {
        throw std::runtime_error("[ERROR] Set flag failed" + std::to_string(errno));
    }
}

inline int networking::NetworkUtility::createSocket(int domain, int type, int protocol) {
    int sock = ::socket(domain, type, protocol);
    if (sock < 0) {
        throw std::runtime_error("[ERROR] Create socket failed" + std::to_string(errno));
    }
    return sock;
}

inline void networking::NetworkUtility::bind(int sock, const sockaddr_in *addr, socklen_t len) {
    if (::bind(sock,(sockaddr*) addr, len) < 0) {
        throw std::runtime_error("[ERROR] Bind failed" + std::to_string(errno));
    }
}

inline void networking::NetworkUtility::listen(int sock, int backlog) {
    if (::listen(sock, backlog)) {
        throw std::runtime_error("[ERROR] Listen failed" + std::to_string(errno));
    }
}

inline int networking::NetworkUtility::accept(int sock, sockaddr *addr, socklen_t *addrlen) {
    int client_fd = ::accept(sock, addr, addrlen);
    if (client_fd < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return -1;
        }
        throw std::runtime_error("[ERROR] Accept failed" + std::to_string(errno));
    }
    return client_fd;
}

inline int networking::NetworkUtility::connect(int sock, const sockaddr *addr, socklen_t len) {
    int sock_fd = ::connect(sock, addr, len);
    if (sock_fd == -1 && errno != EINPROGRESS) {
        throw std::runtime_error("[ERROR] Connect failed" + std::to_string(errno));
    }
    return sock_fd;
}

inline ssize_t networking::NetworkUtility::read(int fd, void *buffer, size_t count) {
    int bytes_read = ::read(fd, buffer, count);
    /**
     * Shouldn't check == -1 here
     * Since in epoll mode, -1 but errno = EAGAIN or EWOULDBLOCK => it's still valid, shouldn't throw error here
     */
    // if (bytes_read < 0) {
    //     throw std::runtime_error("[ERROR] Read failed" + std::to_string(errno));
    // }
    return bytes_read;
}

inline ssize_t networking::NetworkUtility::write(int fd, void *buffer, size_t count) {
    int bytes_write = ::write(fd, buffer, count);
    /**
     * Shouldn't check == -1 here
     * Since in epoll mode, -1 but errno = EAGAIN or EWOULDBLOCK => it's still valid, shouldn't throw error here
     */
    // if (bytes_write < 0) {
    //     throw std::runtime_error("[ERROR] Write failed" + std::to_string(errno));
    // }
    return bytes_write;
}

inline void networking::NetworkUtility::close(int fd) noexcept {
    ::close(fd);
}

#endif //EX01_NETWORKUTILITY_H