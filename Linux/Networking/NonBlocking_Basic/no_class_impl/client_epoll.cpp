//
// Created by tuo8hc on 10/19/25.
//
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int setNonBlocking(int fd){
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1){
        std::cerr << "[ERROR] : Get flag failed" << std::endl;
        return -1;
    }

    if(fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1){
        std::cerr << "[ERROR] : Set flag failed" << std::endl;
        return -1;
    }
    return EXIT_SUCCESS;
}


int main(int argc, char* argv[]) {
    if (argc > 3) {
        std::cerr << "More arg, please check the number of arg" << std::endl;
    }

    std::string ip = argv[1];
    uint16_t port = std::stoi(argv[2]);

    constexpr int MAX_EVENTS = 1024;

    //  Create socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        std::cerr << "Failed to create socket" << std::endl;
        return EXIT_FAILURE;
    }
    
    struct sockaddr_in server{};
    std::memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if(inet_pton(AF_INET, ip.c_str(), &server.sin_addr) == -1){
        std::cerr << "[ERROR] : Invalid ip address" << std::endl;
        close(sock_fd);
        return EXIT_FAILURE;
    }

    if(connect(sock_fd, (sockaddr *) &server, (socklen_t) sizeof(server)) < 0){
        if(errno == EINPROGRESS){

        }
        else{
            std::cerr << "[ERROR] : Connect failed" << std::endl;
            close(sock_fd);
            return EXIT_FAILURE;
        }

    }

    if(setNonBlocking(sock_fd) < 0){
        close(sock_fd);
        return EXIT_FAILURE;
    }

    int epoll_fd = epoll_create1(0);
    if(epoll_fd == -1){
        std::cerr << "[ERROR] : Create epoll instance failed" << std::endl;
        close(sock_fd);
        return EXIT_FAILURE;
    }

    epoll_event ev {};
    std::vector<struct epoll_event> events(MAX_EVENTS);

    ev.data.fd = sock_fd;
    ev.events = EPOLLIN | EPOLLET;
    
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev) < 0){
        std::cerr << "[ERROR] : Add event to epoll list failed" << std::endl;
        close(epoll_fd);
        close(sock_fd);
        return EXIT_FAILURE;
    }

    ev.data.fd = STDIN_FILENO;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0){
        std::cerr << "[ERROR] : Add event to epoll list failed" << std::endl;
        close(epoll_fd);
        close(sock_fd);
        return EXIT_FAILURE;
    }

    while(true){
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        if(num_events < 0){
            std::cerr << "[ERROR] : Epoll wait failed" << std::endl;
            break;
        }

        for(int i = 0; i < num_events; i++){
            int fd = events[i].data.fd;
            if(fd == sock_fd){
                char buff[1024];
                std::memset(buff, 0, sizeof(buff));
                ssize_t bytes_read = recv(sock_fd, buff, sizeof(buff), 0);
                if (bytes_read > 0) {
                    std::cout << "Server echo: " << buff << std::endl;
                }
                else if (bytes_read == 0){
                    std::cout << "Disconnected from server\n";
                    close(epoll_fd);
                    close(sock_fd);
                    return EXIT_FAILURE;
                }
                else {
                    if (errno != EAGAIN || errno != EWOULDBLOCK) {
                        std::cerr << "[ERROR]: read failed" << std::endl;
                        break;
                    }
                }
            }
            else if(fd == STDIN_FILENO){
                std::string msg;
                getline(std::cin, msg);
                send(sock_fd, msg.c_str(), msg.size(), 0);
            }
        }
    }

    return EXIT_SUCCESS;
}
