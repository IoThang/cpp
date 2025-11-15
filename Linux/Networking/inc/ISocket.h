//
// Created by tuo8hc on 10/11/25.
//

#ifndef EX01_ISOCKET_H
#define EX01_ISOCKET_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class ISocket {
public:
    virtual ~ISocket() = default;
    virtual int get_fd() const = 0;
    virtual int bind(int port) = 0;
    virtual int listen(int backlog) = 0;
    virtual int accept(sockaddr_in& client_addr, socklen_t& addr_len) = 0;
    virtual int connect(const std::string& host, int port) = 0;
    virtual int send(std::string const& msg) = 0;
    virtual int recv(std::string& buf) = 0;
    virtual void close() = 0;
};

#endif //EX01_ISOCKET_H