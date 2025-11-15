//
// Created by tuo8hc on 10/17/25.
//

#ifndef EX01_ECHOSERVER_H
#define EX01_ECHOSERVER_H
#include <unordered_map>

#include "Epoll.h"
#include "Socket.h"
#include "NetworkUtils.h"
#include <netinet/in.h>

constexpr int MAX_NUMBERS = 1024;

class EchoServer {
public:
    EchoServer();
    ~EchoServer() = default;

    EchoServer(const EchoServer&) = delete;
    EchoServer& operator=(const EchoServer&) = delete;

    void Start(int port);
    void Stop();
private:
    Socket listen_socket_;
    Epoll epoll_;
    std::unordered_map<int, std::string> clientInfo_;
    bool running_;

    void createListenSocket(int port);
    void eventLoop();
    void handleEvent(const struct epoll_event& event);
    void handleNewConnection();
    void handleClientData(int clientFd);
    bool echoData(int fd, const char* data, size_t len);
    void closeClient(int fd);
};


#endif //EX01_ECHOSERVER_H