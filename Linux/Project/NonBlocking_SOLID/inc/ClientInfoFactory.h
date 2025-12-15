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
        static std::unique_ptr<ClientInfo> create(int fd);
        static void updateRoom(ClientInfo& clientInfo,const std::string& newRoom);
    };
}



#endif //EX01_CLIENTINFOFACTORY_HM