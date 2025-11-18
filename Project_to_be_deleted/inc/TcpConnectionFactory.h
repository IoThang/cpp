//
// Created by TUO8HC on 10/10/2025.
//

#ifndef NETWORKING_TCPCONNECTIONFACTORY_H
#define NETWORKING_TCPCONNECTIONFACTORY_H

#include "IConnectionFactory.h"

class TcpConnectionFactory : public IConnectionFactory {
public:
    std::unique_ptr<TcpConnection> create(SOCKET s) override;
};

#endif //NETWORKING_TCPCONNECTIONFACTORY_H