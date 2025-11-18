//
// Created by tuo8hc on 10/14/25.
//

#ifndef EX01_CLIENTHANDLER_H
#define EX01_CLIENTHANDLER_H

#include <string>
#include <memory>

#include "ISocket.h"

class ClientHandler {
public:
    ClientHandler(std::unique_ptr<ISocket> socket);
    void handleEvent(int fd, uint32_t events);
    int get_fd() const;
private:
    std::string buffer_;
    std::unique_ptr<ISocket> socket_;
};


#endif //EX01_CLIENTHANDLER_H