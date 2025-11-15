//
// Created by TUO8HC on 10/9/2025.
//

#ifndef THREAD_POOL_CLIENT_H
#define THREAD_POOL_CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

class TcpClient {
public:
    explicit TcpClient(std::string const& ip = "127.0.0.1", int const port = 8000);
    ~TcpClient();
    bool connectToServer();
    bool sendMessage(std::string const& message);
    std::string receiveMessage();
    bool isConnected() const;
private:
    SOCKET clientSocket_;
    std::string serverIp_;
    int port_;
    bool initialized_{};
};


#endif //THREAD_POOL_CLIENT_H