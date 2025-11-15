//
// Created by tuo8hc on 10/17/25.
//

#ifndef EX01_NETWORKUTILS_H
#define EX01_NETWORKUTILS_H

#include <sys/socket.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>

class NetworkUtils {
public:
    static void setNonBlocking(int fd) {
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags == -1) {
            throw std::runtime_error(std::string("fcntl F_GETFL failed: ") + strerror(errno));
        }

        if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
            throw std::runtime_error(std::string("fcntl F_SETFL failed: ") + strerror(errno));
        }
    };
    static void setReuseAddr(int fd) {
        int reuse  = 1;
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
            throw std::runtime_error(std::string("setting reuse addr failed") + strerror(errno));
        }
    }

    //  Specific for client
    static bool waitForConnection(int fd, int timeoutSec) {

        return true;
    }
};


#endif //EX01_NETWORKUTILS_H