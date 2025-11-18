//
// Created by TUO8HC on 10/10/2025.
//

#ifndef CPP_TCPSERVER_H
#define CPP_TCPSERVER_H
#include <memory>
#include "IConnectionFactory.h"

class TcpServer {
public:
    TcpServer(std::shared_ptr<NetworkManger> m);
    bool start(int port, std::shared_ptr<IConnectionFactory> f);
    void stop();
private:
    SOCKET listen_socket_;
    std::shared_ptr<NetworkManger> mgr_;
    std::shared_ptr<IConnectionFactory> factory_;
};


#endif //CPP_TCPSERVER_H