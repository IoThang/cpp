//
// Created by TUO8HC on 10/10/2025.
//

#ifndef NETWORKING_ICONNECTIONFACTORY_H
#define NETWORKING_ICONNECTIONFACTORY_H

#include <memory>
#include "TcpConnection.h"

class IConnectionFactory {
public:
    virtual ~IConnectionFactory() = default;
    virtual std::unique_ptr<TcpConnection> create(SOCKET s) = 0;
};

#endif //NETWORKING_ICONNECTIONFACTORY_H