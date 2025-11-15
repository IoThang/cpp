//
// Created by tuo8hc on 10/18/25.
//

#ifndef EX01_ECHOCLIENT_H
#define EX01_ECHOCLIENT_H

#include <string>
#include "Socket.h"

class EchoClient {
public:
    EchoClient(const std::string& serverIp, int port);
    void connect();
    bool sendMessage(const std::string& message);
    std::string receiveResponse(size_t expectedLen);
    void sendAndReceive(const std::string& message);
    bool isConnected() const;
private:
    Socket sock_;
    std::string ip;
    int port_;
};


#endif //EX01_ECHOCLIENT_H