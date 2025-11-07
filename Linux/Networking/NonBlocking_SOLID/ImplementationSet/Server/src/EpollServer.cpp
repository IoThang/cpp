//
// Created by tuo8hc on 10/23/25.
//

#include "../inc/EpollServer.h"

networking::EpollServer::EpollServer(int port) : port_(port),
                                                 server_socket_(AF_INET, SOCK_STREAM, IPPROTO_TCP),
                                                 pool_(POOL_SIZE, std::make_unique<DefaultTaskProcessor>(client_map_)) {
    server_socket_.bindAndListen(port_);
    epoll_.add(server_socket_.get_fd(), EPOLLIN);

    server_handler_ = std::make_unique<ServerHandler>(epoll_, client_handlers_, server_socket_.get_fd(), pool_, client_map_);
    stdin_handler_ = std::make_unique<ServerStdinHandler>(epoll_, client_handlers_, pool_);
    epoll_.add(STDIN_FILENO, EPOLLIN);
    std::cout << "[Server] Listening on port " << port << std::endl;
    std::cout << "[Server] Usage: Enter 'msg' for broadcast, or '@fd:msg' for specific (e.g., @5:hello)" << std::endl;
}

//  Handle event loops
void networking::EpollServer::run() {
    std::vector<epoll_event> events(MAX_EVENTS);
    while (true) {
        size_t num_events = epoll_.wait(events);
        // Optional for debugging
        // std::cout << "[DEBUG] There is(are) " << num_events << " event(s)" << std::endl;
        for (int i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;
            event_t ev = events[i].events;
            if (ev & (EPOLLERR | EPOLLHUP)) {
                std::cerr << "[ERROR] Error/HUP on fd " << fd << std::endl;
                pool_.enqueue({TaskType::Cleanup, fd});
                //  Server (reactor): cleanup server side
                cleanupFd(fd);
                continue;
            }
            //  Only handle accept the connections
            if (fd == server_socket_.get_fd()) {
                server_handler_->handle(fd, ev);
            }
            //  Only handler stdin from key broad
            else if (fd == STDIN_FILENO) {
                stdin_handler_->handle(fd, ev);
            }
            //  Only handle receive data from client
            else {
                auto it = client_handlers_.find(fd);
                if (it != client_handlers_.end()) {
                    it->second->handle(fd, ev);
                    // Check for disconnect after read (in handler, but here for safety)
                    ssize_t test_read = NetworkUtility::read(fd, nullptr, 0);
                    if (test_read <= 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                        //  Ok, keep open
                    } else {
                        cleanupFd(fd);
                    }
                }
            }
        }
    }
}

void networking::EpollServer::cleanupFd(int fd) {
    epoll_.remove(fd);
    client_handlers_.erase(fd);
    NetworkUtility::close(fd);
    std::cout << "[Server] Cleaned up fd = " << fd << std::endl;
}
