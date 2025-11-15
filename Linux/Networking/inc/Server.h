//
// Created by tuo8hc on 10/11/25.
//

#ifndef EX01_SERVER_H
#define EX01_SERVER_H
#include <memory>

#include "ISocket.h"


class Server {
public:
    Server(int port, std::unique_ptr<ISocket> socket);
    void run();
private:
    int port_;
    std::unique_ptr<ISocket> socket_;

    virtual void handleClient(int client_fd);
};


#endif //EX01_SERVER_H