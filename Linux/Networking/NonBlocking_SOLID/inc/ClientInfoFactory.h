//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_CLIENTINFOFACTORY_H
#define EX01_CLIENTINFOFACTORY_H
#include <memory>
#include "ClientInfo.h"

namespace networking {

    class ClientInfoFactory {
    public:
        std::unique_ptr<ClientInfo> create(rint fd);
    };
}



#endif //EX01_CLIENTINFOFACTORY_H