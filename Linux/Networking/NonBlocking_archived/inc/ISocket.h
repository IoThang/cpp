//
// Created by tuo8hc on 10/14/25.
//

#ifndef EX01_ISOCKET_H
#define EX01_ISOCKET_H
#include <netinet/in.h>
#include <string>

class ISocket {
public:
    virtual ~ISocket() = default;
    virtual int get_fd() const;
    virtual int bind(int port);
    virtual int listen(int backlog);
    virtual int accept(sockaddr_in&, socklen_t&);
    virtual int connect(std::string const& host, int port);
    virtual int send(std::string const&);
    virtual int recv(std::string&);
    virtual void close();
    virtual void set_non_blocking(bool enable);
};

#endif //EX01_ISOCKET_H