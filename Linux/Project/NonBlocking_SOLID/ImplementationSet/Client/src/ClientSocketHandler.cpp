//
// Created by tuo8hc on 10/24/25.
//

#include "../inc/ClientSocketHandler.h"

void networking::ClientSocketHandler::handle(int fd, networking::event_t events) {
    if (!(events & EPOLLIN)) return;

    char buffer[1024];
    ssize_t bytes_read = NetworkUtility::read(fd, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            std::cout << "[Client fd = " << fd << "] Server disconnected" << std::endl;
        }
        else {
            std::cout << "[Client fd = " << fd << "] Read error" << std::endl;
        }
        exit(0);
    }
    buffer[bytes_read] = '\0';
    std::cout << buffer;  // No endl for prompt
}
