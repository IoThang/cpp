//
// Created by tuo8hc on 10/14/25.
//

#ifndef EX01_TCPSOCKET_H
#define EX01_TCPSOCKET_H
#include <string>
#include <bits/socket.h>
#include <netinet/in.h>

#include "ISocket.h"


class TCPSocket : public ISocket {
public:
    TCPSocket();
    ~TCPSocket() override;
    TCPSocket(const TCPSocket&) = delete;
    TCPSocket& operator=(const TCPSocket&) = delete;

    int create();
    void set_fd(int fd);

    int get_fd() const override;
    int bind(int port) override;
    int listen(int backlog) override;
    int accept(sockaddr_in& client_addr, socklen_t& addr_len) override;
    int connect(const std::string& host, int port) override;
    int send(std::string const& msg) override;
    int recv(std::string& buf) override;
    void close() override;
    void set_non_blocking(bool) override;

private:
    int sock_fd_{};
};


#endif //EX01_TCPSOCKET_H