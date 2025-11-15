//
// Created by tuo8hc on 10/17/25.
//

#ifndef EX01_SOCKET_H
#define EX01_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr int BACKLOG = 1024;

//  ===== RAII Socket Wrapper =====
class Socket {
public:

    Socket();
    ~Socket() noexcept;

    // Disable copy
    Socket(Socket const&) = delete;
    Socket& operator=(Socket const&) = delete;
    // Allow move
    Socket(Socket&&) noexcept;
    Socket& operator=(Socket&&) noexcept;

    void set(int fd);
    int get() const;
    bool valid() const;
    void close() noexcept;
    int release();

private:
    int sock_fd_;
};


#endif //EX01_SOCKET_H