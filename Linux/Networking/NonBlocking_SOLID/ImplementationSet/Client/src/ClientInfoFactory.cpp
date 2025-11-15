//
// Created by tuo8hc on 11/6/25.
//

#include "../../../inc/ClientInfoFactory.h"

std::unique_ptr<networking::ClientInfo> networking::ClientInfoFactory::create(int fd) {
    return std::make_unique<ClientInfo>(fd);
}

void networking::ClientInfoFactory::updateRoom(ClientInfo& clientInfo,const std::string& newRoom) {
    clientInfo.room_id_ = newRoom;
    clientInfo.last_active_ = std::chrono::steady_clock::now();
    clientInfo.msg_count_ = 0; // Reset
}