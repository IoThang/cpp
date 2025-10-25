//
// Created by tuo8hc on 10/22/25.
//

#include "../inc/ServerHandler.h"
#include "ClientHandler.h"

networking::ServerHandler::ServerHandler(Epoll& epoll, std::unordered_map<int, std::unique_ptr<IEventHandler>>& clients, int server_fd)
    : epoll_(epoll), client_handlers_(clients), server_fd_(server_fd){}

void networking::ServerHandler::handle(int fd, event_t events) {
if (fd != server_fd_ || !(events & EPOLLIN)) return;

        int client_fd = NetworkUtility::accept(server_fd_);
        while (client_fd != -1) {  // Accept all pending
            NetworkUtility::setNonBlocking(client_fd);
            auto handler = std::make_unique<ClientHandler>();
            client_handlers_[client_fd] = std::move(handler);
            epoll_.add(client_fd, EPOLLIN | EPOLLET, client_fd);
            std::cout << "[Server] Client connected: fd=" << client_fd << std::endl;
            client_fd = NetworkUtility::accept(server_fd_);
        }
}