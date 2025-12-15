//
// Created by tuo8hc on 10/24/25.
//

#include "../inc/ClientStdinHandler.h"

#include <iostream>

networking::ClientStdinHandler::ClientStdinHandler(int fd) : socket_fd_(fd), isRegistered_(false), isRoomSet_(false)
{}

//  Will refactor later. It seems that mess up at the moment. But It quickly has to be done for interview to show off :))
void networking::ClientStdinHandler::handle(int fd, event_t events) {
    if (!isRegistered_) {
        enterName(socket_fd_);
        isRegistered_ = true;
        return;
    }
    if (!isRoomSet_) {
        enterRoom(socket_fd_);
        isRoomSet_ = true;
        if (isRegistered_ && isRoomSet_) {
            std::cout << "=== Your information already fulfilled. Starting the chat ===" << std::endl;
            std::cout << "=== Send with this syntax SpecificePerson:your message. Otherwise, you chat with server ===" << std::endl;
            return;
        }
    }

    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        //  To disconnect
        //  TODO Refactor command to exit, use #exit
        if (line == "exit") {
            std::string exit_msg = "exit\n";
            NetworkUtility::write(socket_fd_, exit_msg.data(), exit_msg.size());
            std::cout << "[Client] Sent exit request. Disconnecting." << std::endl;
            sleep(1);
            exit(0);  // Client exits after sending
        }

        // =============================================================================================
        //  DOn't remove below this line. It will flush the buffer to write immediately. Without enter or waiting the next entering
        line += "\n";
        ssize_t bytes_written = NetworkUtility::write(socket_fd_, line.data(), line.size());
        if (bytes_written < 0) {
            std::cerr << "[ERROR] ClientStdinHandler::handle(): writing to socket failed" << std::endl;
        }
    }
}

void networking::ClientStdinHandler::enterName(int socket_fd) {
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        line = "[SETNAME]:" + line;
        NetworkUtility::write(socket_fd_, line.data(), line.size());
    }
    std::cout << "[Client] Please enter your room: " << std::endl;
}

void networking::ClientStdinHandler::enterRoom(int socket_fd) {
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) {
        line = "[JOINROOM]:" + line;
        NetworkUtility::write(socket_fd_, line.data(), line.size());
    }
}
