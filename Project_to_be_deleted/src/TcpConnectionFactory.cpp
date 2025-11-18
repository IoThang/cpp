//
// Created by TUO8HC on 10/10/2025.
//

#include "../inc/TcpConnectionFactory.h"

std::unique_ptr<TcpConnection> TcpConnectionFactory::create(SOCKET s) {
    return std::make_unique<TcpConnection>(s);
}
