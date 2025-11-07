//
// Created by tuo8hc on 10/22/25.
//

#include "../inc/ServerStdinHandler.h"

networking::ServerStdinHandler::ServerStdinHandler(Epoll& epoll, std::unordered_map<int, std::unique_ptr<IEventHandler>>& clients, ThreadPool& threadPool)
    : epoll_(epoll), client_handlers_(clients), pool_(threadPool) {}
// ServerStdinHandler: Admin cmds
void networking::ServerStdinHandler::handle(int fd, event_t events) {
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) return;

    if (line == "exit") {
        std::cout << "[Server] Shutting down all clients and exiting." << std::endl;
        // Cleanup all clients
        for (const auto& [fd, _] : client_handlers_) {
            epoll_.remove(fd);
            NetworkUtility::close(fd);
            std::cout << "[Server] Cleaned up fd=" << fd << std::endl;
        }
        client_handlers_.clear();
        exit(0);
    }

    // Parse: If starts with "@fd:", send to specific; else broadcast
    size_t pos = line.find("@");
    if (pos == 0 && line.size() > 1) {
        //  Specific: "@5:hello"
        size_t colon_pos = line.find(":", 1);
        if (colon_pos != std::string::npos) {
            std::string fd = line.substr(1, colon_pos - 1);
            std::string msg = line.substr(colon_pos + 1);
            try {
                int target_fd = std::stoi(fd);
                auto it = client_handlers_.find(target_fd);
                if (it != client_handlers_.end()) {
                    std::string full_msg = "Server to " + std::to_string(target_fd) + " :" + msg + "\n";
                    NetworkUtility::write(target_fd, full_msg.data(), full_msg.size());
                    std::cout << "[Server] Sent to fd=" << target_fd << ": " << msg << std::endl;
                }
                else {
                    std::cout << "[Server] Client fd=" << target_fd << " not found" << std::endl;
                }
            } catch (const std::exception&) {
                std::cout << "[Server] Invalid fd in input" << std::endl;
            }
        }
        else {
            std::cout << "[Server] Invalid format for specific send (use @fd:msg)" << std::endl;
        }
    }
    //  Broadcast
    else {
        std::string full_msg = "Broadcast: " + line + "\n";
        bool sent_any = false;
        for (const auto& [fd, _] : client_handlers_) {
            ssize_t bytes_written = NetworkUtility::write(fd, full_msg.data(), sizeof(full_msg));
            if (bytes_written > 0) {sent_any = true;}
        }
        if (sent_any) {
            std::cout << "[Server] Broadcasted: " << line << std::endl;
        } else {
            std::cout << "[Server] No clients to broadcast" << std::endl;
        }
    }
}
