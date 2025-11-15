//
// Created by tuo8hc on 10/11/25.
//

#include "../inc/SocketFactory.h"

#include "TCPSocket.h"

std::unique_ptr<ISocket> SocketFactory::create() {
    auto s = std::make_unique<TCPSocket>();
    s->create();
    return s;
}
