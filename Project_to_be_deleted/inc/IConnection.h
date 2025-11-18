//
// Created by TUO8HC on 10/10/2025.
//

#ifndef NETWORKING_ICONNECTION_H
#define NETWORKING_ICONNECTION_H

#include <winsock2.h>
#include "Message.h"

class IConnection {
public:
    virtual ~IConnection() = default;

    virtual bool send(Message const& msg) = 0;
    virtual Message receive() = 0;
    virtual void close() = 0;
    virtual bool isConnected() const = 0;
};


#endif //NETWORKING_ICONNECTION_H