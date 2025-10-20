//
// Created by tuo8hc on 10/17/25.
//

#ifndef EX01_NETWORKUTILS_H
#define EX01_NETWORKUTILS_H

#include <sys/socket.h>
#include <fcntl.h>
#include <stdexcept>

class NetworkUtils {
public:
    static void setNonBlocking(int fd);
    static void setReuseAddr(int fd);
};


#endif //EX01_NETWORKUTILS_H