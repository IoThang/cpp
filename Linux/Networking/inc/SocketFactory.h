//
// Created by tuo8hc on 10/11/25.
//

#ifndef EX01_SOCKETFACTORY_H
#define EX01_SOCKETFACTORY_H
#include <memory>
#include "ISocket.h"

class SocketFactory {
public:
    static std::unique_ptr<ISocket> create();
};


#endif //EX01_SOCKETFACTORY_H