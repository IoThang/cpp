//
// Created by tuo8hc on 10/22/25.
//

#include "../inc/ClientHandler.h"

#include <cstring>
#include <iostream>
#include <sys/epoll.h>

// Client handler: Handles incoming messages and echoes (can be extended for broadcast receive)
void networking::ClientHandler::handle(int fd, event_t events) {
    if (!(events & EPOLLIN)) return;
    char buffer[1024];
    ssize_t bytes_read = NetworkUtility::read(fd,buffer,sizeof(buffer) - 1);
    if(bytes_read <= 0) {
        if (bytes_read == 0) {
            // Check for "exit" command from client
            if (strcmp(buffer, "exit\n") != 0) {
                std::cout << "[Server] Client fd=" << fd << " requested exit. Disconnecting." << std::endl;
            } else {
                std::cout << "[Client fd = " << fd << "] Disconnected" << std::endl;
            }
        }
        else {
            std::cerr << "[ERROR] : NetworkUtility::read failed on fd = " << fd << " : " << strerror(errno) << std::endl;
        }
        // Signal disconnect via virtual or callback; here, just close
        NetworkUtility::close(fd);
        return;
    }
    buffer[bytes_read] = '\0';
    std::cout << "[Client fd = " << fd << "] Received: " << buffer << std::endl;

    //  Echo back
    NetworkUtility::write(fd,buffer,static_cast<size_t>(bytes_read));
}
