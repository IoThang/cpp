//
// Created by tuo8hc on 10/12/25.
//

#include <cstring>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    if(argc > 4) {
        std::cerr << "Usage: client <server-ip> <server-port>\n";
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);

    std::cout << "\n=== CLIENT STARTING ===" << std::endl;
    std::cout << "Server IP: " << server_ip << std::endl;
    std::cout << "Port: " << port << "\n" << std::endl;

    // ============================================
    // STEP 1: Create SOCKET
    // ============================================
    std::cout << "Create socket..." << std::endl;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "❌ Socket creation failed..." << std::endl;
    }

    std::cout << "✅ Socket created with FD:" << sock_fd << std::endl;

    // ============================================
    // STEP 2: CONNECT - Connect to server
    // ============================================
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    //  Convert IP string to binary
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "❌ Failed: IP invalid: " << server_ip << std::endl;
        close(sock_fd);
        return 1;
    }

    if (connect(sock_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "❌ Failed: Can not connect to server" << std::endl;
        std::cerr << "❌ Have the server start yet ?" << std::endl;
        close(sock_fd);
        return 2;
    }

    std::cout << "✅ Connected to " << server_ip << ":" << port << "\n" << std::endl;

    // ============================================
    // STEP 3: SEND - Send message to server
    // ============================================
    std::cout << "Send message to server. Chat loop started ..." << std::endl;
    std::string message;

    while (true) {
        std::cout << "Client (>): ";  // Prompt
        std::getline(std::cin, message);  // Lấy cả dòng
        if (message.empty()) continue;  // Bỏ qua nếu rỗng

        if (send(sock_fd, message.c_str(), message.size(), 0) < 0) {
            std::cerr << "❌ Failed: Failed to send message!" << std::endl;
            break;
        }

        if (message == "quit" || message == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
    }

    // ============================================
    // STEP 5: CLOSE - Close socket
    // ============================================
    std::cout << "Close socket..." << std::endl;

    close(sock_fd);
    std::cout << "✅ Closed socket" << std::endl;

    std::cout << "\n=== CLIENT STOPPED ===" << std::endl;
    return 0;
}