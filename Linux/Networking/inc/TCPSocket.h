//
// Created by tuo8hc on 10/11/25.
//

#ifndef EX01_TCPSOCKET_H
#define EX01_TCPSOCKET_H
#include "ISocket.h"

// Low-level of socket
class TCPSocket : public ISocket {
public:
    TCPSocket();
    ~TCPSocket() override;

    int create();
    
    int get_fd() const override;
    int bind(int port) override;
    int listen(int backlog) override;
    int accept(sockaddr_in& client_addr, socklen_t& addr_len) override;
    int connect(const std::string& host, int port) override;
    int send(std::string const& msg) override;
    int recv(std::string& buf) override;
    void close() override;
private:
    int socket_;
};


#endif //EX01_TCPSOCKET_H