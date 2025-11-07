//
// Created by tuo8hc on 11/6/25.
//

#include "../../../inc/ClientInfoFactory.h"

std::unique_ptr<networking::ClientInfo> networking::ClientInfoFactory::create(int fd) {
    return std::make_unique<ClientInfo>(fd);
}
