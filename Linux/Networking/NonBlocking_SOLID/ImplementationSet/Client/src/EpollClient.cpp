//
// Created by tuo8hc on 10/24/25.
//

#include "../inc/EpollClient.h"

#include "ClientStdinHandler.h"


networking::EpollClient::EpollClient(std::string host, port_type port) : socket_(Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) {
    socket_.connectTo(host, port);
    epoll_.add(socket_.get_fd(), EPOLLIN | EPOLLET, socket_.get_fd());
    socket_handler_ = std::make_unique<ClientSocketHandler>();
    stdin_handler_ = std::make_unique<ClientStdinHandler>(socket_.get_fd());
    // Add stdin to epoll
    epoll_.add(STDIN_FILENO, EPOLLIN | EPOLLET);
    std::cout << "[Client "<< socket_.get_fd() <<" ] Connected to " << host << ":" << port << ". Type messages to send." << std::endl;
}

void networking::EpollClient::run() {
    std::vector<epoll_event> events(MAX_EVENTS);

    while (true) {
        size_t num_events = epoll_.wait(events, -1);

        for (size_t i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;
            event_t ev = events[i].events;
            if (ev & (EPOLLERR | EPOLLHUP)) {
                std::cerr << "[ERROR] Error/HUP on fd " << fd << std::endl;
                break;
            }
            //  Event: From server (EPOLLIN)
            if (fd == socket_.get_fd()) {
                socket_handler_->handle(fd, ev);
            }
            //  Event: From KEYBOARD
            else if (fd == STDIN_FILENO) {
                stdin_handler_->handle(fd, ev);
            }
        }

    }
}

