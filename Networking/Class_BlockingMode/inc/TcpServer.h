//
// Created by TUO8HC on 10/9/2025.
//

#ifndef THREAD_POOL_SERVER_H
#define THREAD_POOL_SERVER_H

#include <winsock2.h>
#include <string>
#include <iostream>

class TcpServer {
public:
    explicit TcpServer(int const port = 8000);
    ~TcpServer();

    bool start();
    bool sendMessage(std::string message);
    std::string receiveMessage();
    bool isConnected() const;
private:
    //  Main socket of server (listen)
    SOCKET server_fd_{};
    //  Socket which is done for client connection
    SOCKET client_fd_{};
    //  Port to listen
    int port_{};
    //  Flag to ckeck whether WSAStartup is successful
    bool initialized_{};
};

#endif //THREAD_POOL_SERVER_H