//
// Created by tuo8hc on 10/22/25.
//

#include "../inc/ServerHandler.h"
#include "ClientHandler.h"

networking::ServerHandler::ServerHandler(Epoll& epoll, std::unordered_map<int, std::unique_ptr<IEventHandler>>& clients, int server_fd, ThreadPool& thread_pool, std::unordered_map<int, std::string>& client_map)
    : epoll_(epoll), client_handlers_(clients), server_fd_(server_fd), pool_(thread_pool), client_map_(client_map){}

void networking::ServerHandler::handle(int fd, event_t events) {
    if (fd != server_fd_ || !(events & EPOLLIN)) return;

    int client_fd = NetworkUtility::accept(server_fd_);
    while (client_fd != -1) {  // Accept all pending
        NetworkUtility::setNonBlocking(client_fd);
        {
            std::unique_lock<std::shared_mutex> wlock(client_mutex_);
            client_map_[client_fd] = "Client_" + std::to_string(client_fd);
        }
        auto handler = std::make_unique<ClientHandler>();
        client_handlers_[client_fd] = std::move(handler);
        epoll_.add(client_fd, EPOLLIN | EPOLLET, client_fd);
        std::cout << "[Server] Client connected: fd=" << client_fd << std::endl;
        client_fd = NetworkUtility::accept(server_fd_);
    }
}