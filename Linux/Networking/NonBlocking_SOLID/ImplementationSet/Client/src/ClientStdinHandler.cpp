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
        //  To disconnect
        //  TODO Refactor command to exit, use #exit
        if (line == "exit") {
            std::string exit_msg = "exit\n";
            NetworkUtility::write(socket_fd_, exit_msg.data(), exit_msg.size());
            std::cout << "[Client] Sent exit request. Disconnecting." << std::endl;
            exit(0);  // Client exits after sending
        }

        //  Handle set name task
        size_t open_pos = line.find("[", 0);
        size_t close_pos = line.find("]", 1);
        std::string task = line.substr(open_pos, close_pos - open_pos);
        if (task == "SETNAME") {
            std::string buffer = line.substr(close_pos + 1);

        }
        // =============================================================================================
        line += "\n";
        ssize_t bytes_written = NetworkUtility::write(socket_fd_, line.data(), line.size());
        if (bytes_written < 0) {
            std::cerr << "[ERROR] ClientStdinHandler::handle(): writing to socket failed" << std::endl;
        }
    }
}
