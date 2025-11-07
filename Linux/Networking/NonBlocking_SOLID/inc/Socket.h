//
// Created by tuo8hc on 10/21/25.
//

#ifndef EX01_SOCKET_H
#define EX01_SOCKET_H
#include <string>
#include <netinet/in.h>

#include "NetworkUtility.h"

namespace networking {
    using port_type = uint16_t;


    class Socket {
    public:
        Socket(int fd);
        Socket(int domain, int type, int protocol);
        ~Socket() = default;
        //  Disable copy
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;
        //  Allow move
        Socket(Socket&& other);
        Socket& operator = (Socket&& other) noexcept;

        int get_fd() const noexcept;
        void bindAndListen(port_type port, int backlog = SOMAXCONN);
        void connectTo(std::string& host, port_type port);
        Socket accept();
    private:
        int fd_;
        void close() noexcept;
    };
}


#endif //EX01_SOCKET_H