//
// Created by tuo8hc on 10/16/25.
//

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <cerrno>

int set_non_blocking(int fd) {
    int flag = fcntl(fd, F_GETFL);
    if (flag == -1) {
        perror("get flag fd failed");
        return -1;
    }

    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1) {
        perror("set non-blocking fd failed");
        return -1;
    }

    return EXIT_SUCCESS;
}

//  No need in this case
// int handleNewConnection(int server_fd) {
//     struct sockaddr_in addr{};
//     socklen_t addr_size = sizeof(addr);
//     return accept(server_fd,(sockaddr*) &addr, &addr_size);
// }

std::vector<int> clientFiltering(std::string& msg, std::vector<int> const& clients) {
    std::vector<int> filter(0);
    std::string temp{};

    ssize_t firstSlash = msg.find('/');
    if (firstSlash == std::string::npos) return filter;

    ssize_t secondSlash = msg.find('/', firstSlash + 1);
    if (secondSlash == std::string::npos) return filter;

    // Lấy phần giữa hai dấu '/'
    std::string content = msg.substr(firstSlash, secondSlash - firstSlash + 1);
    msg.erase(firstSlash, secondSlash + 1);

    //  Parse msg to get client fd
    for (auto c : content) {
        if (c == '-' || c == '/') {
            if(!temp.empty()){
                int val = std::stoi(temp);
                bool valid = false;
                for (auto v : clients) {
                    if (val == v) {
                        filter.push_back(v);
                        valid = true;
                    }
                }
                temp.clear();
            }
        }
        else {
            temp += c;
            std::cout << temp << std::endl;
        }
    }
    return filter;
    return filter;
}

void broadcast(std::vector<int> const& client, int sender, std::string& msg) {
    //  Parse message to see send for specific client or boardcast
    std::vector<int> listOfClients = clientFiltering(msg, client);
    if (listOfClients.empty()) {
        std::cout << "=========== Broadcast mode =====" << std::endl;
        listOfClients = client;
    }
    else {
        std::cout << "============ Specific client fd mode =====" << std::endl;
    }

    for (int fd : listOfClients) {
        if (fd != sender) {
            std::string pattern = "[SERVER] " + msg + "\n";
            send(fd, msg.c_str(), msg.size(), 0);
        }
    }
}

int main(int argc, char* argv[]) {

    int PORT = std::stoi(argv[1]);

    constexpr int BACKLOG = 10;
    constexpr int MAX_EVENTS = 100;

    //  Create and config listen socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        return EXIT_FAILURE;
    }
    //  Allow to reuse ip.port
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("listen");
        close(server_fd);
        return EXIT_FAILURE;
    }

    // Set non-blocking here
    if (set_non_blocking(server_fd) < 0) {
        perror("set_non_blocking");
        close(server_fd);
        return EXIT_FAILURE;
    }

    //  Create epoll instance
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(server_fd);
        close(epoll_fd);
        return EXIT_FAILURE;
    }

    //  Register socket server with epoll to track events
    struct epoll_event event;
    event.data.fd = server_fd;
    event.events = EPOLLIN | EPOLLET;   //  Track read event and config ET mode

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        perror("epoll_ctl");
        close(server_fd);
        close(epoll_fd);
        return EXIT_FAILURE;
    }

    //  For broadcase message from stdin
    event.data.fd = STDIN_FILENO;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl");
        close(server_fd);
        close(epoll_fd);
        return EXIT_FAILURE;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    std::vector<struct epoll_event> events(MAX_EVENTS);
    char buffer[1024];
    //  List of client for boardcast feature
    std::vector<int> clients;
    //  Events loop
    while (true) {
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        std::cout << "There is " << num_events << " event(s)" << std::endl;
        if (num_events == -1) {
            perror("epoll_wait");
            break;
        }
        for (int i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;
            if (fd == server_fd) {
                //  Event in socket server: New connection
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
                if (client_fd == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        //  There is no waiting connection. This is a normal behavior of non-blocking socket
                        break;
                    }
                    else {
                        perror("accept");
                        continue;
                    }
                }
                set_non_blocking(client_fd);

                //  Add new client socket to epoll
                event.data.fd = client_fd;
                event.events = EPOLLIN | EPOLLET;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
                    perror("epoll_ctl add client failed");
                    close(client_fd);
                }
                clients.push_back(client_fd);
                std::cout << "[Client fd = " << client_fd << "] Connected" << std::endl;
            }
            else if (fd == STDIN_FILENO) {
                std::string msg;
                std::getline(std::cin, msg);
                broadcast(clients, -1, msg);
            }
            else if (events[i].events == EPOLLIN) {
                //  Event in client socket: New data to read
                // int client_fd = events[i].data.fd;
                ssize_t bytes_read = read(fd, buffer, 1024);

                if (bytes_read <= 0) {
                    //  Issue or client disconnection
                    if (bytes_read == 0) {
                        std::cout << "Client disconnected fd = " << fd  << std::endl;
                    }
                    else {
                        perror("read");
                    }

                    //  Clean-up: remove out of epoll and close socket
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
                    std::cout << "[Client fd = " << fd << "] Disconnected" << std::endl;
                    close(fd);
                    goto CLOSE;
                }
                else {
                    std::cout << "[Client fd = " << fd << "] Write " << bytes_read << " bytes : " << buffer << std::endl;
                    write(fd, buffer, bytes_read);
                }
            }
        }
    }
    CLOSE:
    close(server_fd);
    close(epoll_fd);
    
    return EXIT_SUCCESS;
}