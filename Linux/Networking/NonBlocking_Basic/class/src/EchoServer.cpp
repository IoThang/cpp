//
// Created by tuo8hc on 10/17/25.
//

#include "../inc/EchoServer.h"

#include <vector>

#include "../inc/NetworkUtils.h"


void EchoServer::createListenSocket(int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        throw std::runtime_error(std::string("socket failed") + strerror(errno));
    }

    listen_socket_ = sock_fd;

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listen_socket_.get(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        //  TODO: Is this necessary to call close. Since when throw happens, it will call deconstructor to close it
        listen_socket_.close();
        throw std::runtime_error(std::string("bind failed") + strerror(errno));
    }

    if (listen(listen_socket_.get(), BACKLOG) == -1) {
        listen_socket_.close();
        throw std::runtime_error(std::string("listen failed") + strerror(errno));
    }

    NetworkUtils::setNonBlocking(listen_socket_.get());
    NetworkUtils::setReuseAddr(listen_socket_.get());
}

void EchoServer::eventLoop() {
    std::vector<struct epoll_event> events(MAX_NUMBERS);

    while (running_) {
        int num_events = epoll_.wait(events.data(), MAX_NUMBERS, -1);
        if (num_events == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by signal, retry
            }
            std::cerr << "epoll_wait failed: " << strerror(errno) << std::endl;
            break;
        }

        std::cout << "→ epoll_wait returned " << num_events << " event(s)" << std::endl;
        for (int i = 0; i < num_events; i++) {
            handleEvent(events[i]);
        }
        std::cout << std::endl;
    }
}

void EchoServer::handleEvent(const struct epoll_event& event) {
    //  Check for error
    if (event.events & EPOLLERR) {
        std::cerr << "! EPOLLERR on fd=" << event.data.fd << std::endl;
        closeClient(event.data.fd);
        return;
    }
    if (event.events & EPOLLHUP) {
        std::cout << "! EPOLLHUP on fd=" << event.data.fd << std::endl;
        closeClient(event.data.fd);
        return;
    }

    // Handle events
    if (event.events & EPOLLIN) {
        if (event.data.fd == listen_socket_.get()) {
            handleNewConnection();
        }
        else {
            handleClientData(event.data.fd);
        }
    }
}

void EchoServer::handleNewConnection(int clientFd) {

}
