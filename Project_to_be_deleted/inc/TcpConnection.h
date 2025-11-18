//
// Created by TUO8HC on 10/10/2025.
//

#ifndef NETWORKING_TCPCONNECTION_H
#define NETWORKING_TCPCONNECTION_H

#include "IConnection.h"
#include <string>

class TcpConnection : public IConnection {
public:
    explicit TcpConnection(SOCKET sock);
    ~TcpConnection() override;

    bool send(Message const &msg) override;
    Message receive() override;
    void close() override;
    bool isConnected() const override;

    std::string serialize(Message const& msg);
    Message deserialize(std::string const& data);

private:
    SOCKET socket_;
    bool connected_;
};

#endif //NETWORKING_TCPCONNECTION_H