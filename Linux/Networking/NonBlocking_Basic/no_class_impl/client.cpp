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
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <cerrno>
#include <bits/fs_fwd.h>

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

int main(int argc, char* argv[]) {
    std::string ip = (argv[1]);
    int port = std::stoi(argv[2]);

    constexpr int buff_size = 1024;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return EXIT_FAILURE;
    }

    set_non_blocking(sock_fd);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) < 0) {
        std::cerr << "Invalid ip address " << ip << std::endl;
    }

    //  Connect non-blocking to server
    int ret = connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
        if (errno != EINPROGRESS) {
            perror("Connect failed");
            close(sock_fd);
            return EXIT_FAILURE;
        }

        // EINPROGRESS có nghĩa là kết nối đang được thực hiện ngầm.
        // Chúng ta sẽ dùng select() để chờ nó hoàn tất.
        std::cout << "Connecting ..." << std::endl;
    }
    if (ret == 0) {
        std::cout << "Connection established immediately" << std::endl;
    }

    //  Create a set fds to track event trigger
    fd_set read_fds, write_fds;
    char buffer[buff_size];
    bool connected = false;

    while (true) {
        //  Set 0 bit for all bit of set
        FD_ZERO(&read_fds);
        //  Always track input from keyboard (file descriptor 0). (Register and only track in this index)
        FD_SET(STDIN_FILENO, &read_fds);
        // Always track "readable" event to receive data from server (Register and only track in this index)
        FD_SET(sock_fd, &read_fds);

        //  Find max number of FD to pass to select()
        int maxfd = (sock_fd > STDIN_FILENO) ? sock_fd : STDIN_FILENO;
        //  Waiting event trigger of already register FD
        int activity = select(maxfd + 1, &read_fds, nullptr, nullptr, nullptr);

        if (activity < 0) {
            perror("select error");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            std::string line;
            std::getline(std::cin, line);
            if (line == "quit") {
                break;
            }
            send(sock_fd, line.c_str(), line.size(), 0);
        }

        //  Handle event: Data available from server
        if (FD_ISSET(sock_fd, &read_fds)) {
            memset(buffer, 0, buff_size);
            ssize_t bytes_read = read(sock_fd, buffer, buff_size);
            if (bytes_read > 0) {
                std::cout << "Server echo: " << buffer << std::endl;
                std::cout << "Client> " << std::flush;
            }
            else if (bytes_read == 0) {
                std::cout << "Server disconnected" << std::endl;
                break;
            }
            else {
                if (errno != EAGAIN || errno != EWOULDBLOCK) {
                    perror("read failed");
                    break;
                }
            }
        }

    }

    std::cout << "Closed connection" << std::endl;
    close(sock_fd);

    return EXIT_SUCCESS;
}


/*
while (true) {
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);

        //  Always track input from keyboard (file descriptor 0)
        FD_SET(STDIN_FILENO, &read_fds);

        if (!connected) {
            //  If not connected yet, track "writable" event to know when connect() complete
            FD_SET(sock_fd, &write_fds);
        }
        else {
            //  If connected, track "readable" event to receive data from server
            FD_SET(sock_fd, &read_fds);
        }
        //  Find max of FD to pass to select()
        int maxfd = (sock_fd > STDIN_FILENO) ? sock_fd : STDIN_FILENO;
        //  Waiting event trigger of already register FD
        int activity = select(maxfd + 1, &read_fds, &write_fds, nullptr, nullptr);

        if (activity < 0) {
            perror("select error");
            break;
        }

        //  Handle the event of completed connection
        if (FD_ISSET(STDIN_FILENO, &write_fds) && !connected) {
            int opt_val;
            socklen_t opt_len = sizeof(opt_val);
            if (getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &opt_val, &opt_len) == 0 && opt_val == 0) {
                connected = true;
                std::cout << "Connect successfully to server !" << std::endl;
            }
            else {
                std::cerr << "Failed to connect to server" << std::endl;
                break;
            }
        }

        //  Handle event: Data available from server
        if (FD_ISSET(sock_fd, &read_fds) && !connected) {
            memset(buffer, 0, buff_size);
            ssize_t bytes_read = read(sock_fd, buffer, buff_size);
            if (bytes_read > 0) {
                std::cout << "Server echo: " << buffer << std::endl;
                std::cout << "Client> " << std::flush;
            }
            else if (bytes_read == 0) {
                std::cout << "Server disconnected" << std::endl;
                break;
            }
            else {
                if (errno != EAGAIN || errno != EWOULDBLOCK) {
                    perror("read failed");
                    break;
                }
            }
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            std::string line;
            if (std::getline(std::cin, line)) {
                if (line == "quit") {
                    break;
                }

                if (connected) {
                    send(sock_fd, line.c_str(), line.size(), 0);
                }
                else {
                    std::cout <<" Not yet connected, please wait ..." << std::endl;
                }
            }
            else {
                break;
            }
        }

        if (connected) {
            std::cout << "Client> " << std::flush;
        }
    }
*/