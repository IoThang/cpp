//
// Created by tuo8hc on 10/17/25.
//

#include "../inc/EchoServer.h"

#include <vector>
#include <arpa/inet.h>

EchoServer::EchoServer() : running_(false) {}

void EchoServer::Start(int port) {
    std::cout << "=== Non-blocking Echo Server (C++) ===" << std::endl;
    std::cout << "Starting server on port " << port << "..." << std::endl << std::endl;

    //  Create and configure listening socket
    createListenSocket(port);

    //  Add to epoll
    epoll_.add(listen_socket_.get(), EPOLLIN | EPOLLET);

    std::cout << "✓ Server listening on 0.0.0.0:" << port << std::endl;
    std::cout << "✓ Epoll initialized with edge-triggered mode" << std::endl;
    std::cout << "✓ Waiting for connections..." << std::endl << std::endl;

    // Start event loop
    running_ = true;
    eventLoop();
}

void EchoServer::Stop() {
    running_ = false;
}

void EchoServer::createListenSocket(int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        throw std::runtime_error(std::string("socket failed") + strerror(errno));
    }

    listen_socket_.set(std::move(sock_fd));

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

void EchoServer::handleNewConnection() {
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);
        int client_fd = accept(listen_socket_.get(), reinterpret_cast<sockaddr*>(&client_addr), &client_addr_length);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            else {
                std::cerr << "accept failed: " << strerror(errno) << std::endl;
                break;
            }
        }
        try {
            NetworkUtils::setNonBlocking(client_fd);

            // Add new client socket to epoll
            epoll_.add(client_fd, EPOLLIN | EPOLLET);

            // Store client info
            std::string info = std::string(inet_ntoa(client_addr.sin_addr)) +
                              ":" + std::to_string(ntohs(client_addr.sin_port));
            clientInfo_[client_fd] = info;

            std::cout << "Client added with fd = " << client_fd << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error handling new connection: " << e.what() << std::endl;
            ::close(client_fd);
        }
    }

}

void EchoServer::handleClientData(int clientFd) {
    std::vector<char> buffer(MAX_NUMBERS);
    ssize_t total_read = 0;

    while (true) {
        ssize_t bytes_read = read(clientFd, buffer.data(), buffer.size());
        if (bytes_read == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                //  Finished reading
                if (total_read > 0) {
                    std::cout << "-> Read " << total_read << " bytes of fd : " << clientFd << std::endl;
                }
                break;
            }
            else {
                std::cerr << "read failed: " << strerror(errno) << std::endl;
                closeClient(clientFd);
                return;
            }
        }
        else if (bytes_read == 0) {
            //  Client closed connection
            std::cout << "-> Connection closed on fd : " << clientFd << std::endl;
            closeClient(clientFd);
            return;
        }
        total_read += bytes_read;

        //  Echo data back
        if (!echoData(clientFd, buffer.data(), bytes_read)) {
            closeClient(clientFd);
            return;
        }

        std::cout << "  → Echoed " << bytes_read << " bytes to fd=" << clientFd << std::endl;
    }
}

bool EchoServer::echoData(int client_fd, const char* data, size_t len) {
    ssize_t total_written = 0;
    while (total_written < len) {
        ssize_t bytes_written = write(client_fd, data + total_written, len - total_written);
        if (bytes_written == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // Would block, retry
                usleep(1000);
                continue;
            }
            else {
                std::cerr << "write failed on fd=" << client_fd << ": " << strerror(errno) << std::endl;
                return false;
            }
        }
        total_written += bytes_written;
    }
    return true;
}

void EchoServer::closeClient(int client_fd) {
    epoll_.remove(client_fd);
    clientInfo_.erase(client_fd);
    ::close(client_fd);
}
