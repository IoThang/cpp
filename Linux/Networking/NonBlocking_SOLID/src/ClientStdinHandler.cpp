//
// Created by tuo8hc on 10/24/25.
//

#include "../inc/ClientStdinHandler.h"

#include <iostream>

networking::ClientStdinHandler::ClientStdinHandler(int fd) : socket_fd_(fd) {
}

void networking::ClientStdinHandler::handle(int fd, event_t events) {
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        line += "\n";
        ssize_t bytes_written = NetworkUtility::write(socket_fd_, line.data(), line.size());
        if (bytes_written < 0) {
            std::cerr << "[ERROR] ClientStdinHandler::handle(): writing to socket failed" << std::endl;
        }
    }
}
