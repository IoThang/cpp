//
// Created by tuo8hc on 10/11/25.
//

#include "../inc/Server.h"

#include <iostream>

#include "TCPSocket.h"

Server::Server(int port, std::unique_ptr<ISocket> socket) : port_(port), socket_(std::move(socket)) {
    if (socket_->bind(port_) < 0) {
        throw std::runtime_error("Server: bind failed");
    }
    if (socket_->listen(5) < 0) {
        throw std::runtime_error("Server: listen failed");
    }
}
void Server::handleClient(int client_fd) {
    std::string buffer;
    if (socket_->recv(buffer) > 0) {
        std::cout << "Server: received message: " << buffer << std::endl;
        std::string echo ="Echo " + buffer;
        socket_->send(echo);
    }
}


void Server::run() {
    std::cout << "Server: listening on port " << port_ << std::endl;
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = socket_->accept(client_addr, client_len);
        if (client_fd < 0) {
            throw std::runtime_error("Server: accept failed");
            continue;
        }
        auto client_socket = std::make_unique<TCPSocket>();
        handleClient(client_fd);
        ::close(client_fd);
    }
}
