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
    if (argc > 2) {
        std::cerr << "Usage: server [port]" << std::endl;
    }
    // ============================================
    // STEP 0: Get INPUT - Port number
    // ============================================
    int port = std::stoi(argv[1]);
    std::cout << "\n=== SERVER STARTING ===" << std::endl;

    // ============================================
    // STEP 1: Create SOCKET
    // ============================================
    int server_fd = socket(AF_INET,           /* IPv4 */
                           SOCK_STREAM,
                         IPPROTO_TCP);      /* TCP */

    if (server_fd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
    }

    std::cout << "Server socket created with FD:" << server_fd << std::endl;
    // Socket option: allow reuse address (avoid "Address already in use")
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    std::cout << "✅ Set SO_REUSEADDR\n" << std::endl;

    // ============================================
    // STEP 2: BIND socket to IP:Port
    // ============================================
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;            // IPv4
    server_address.sin_addr.s_addr = INADDR_ANY;    // 0.0.0.0 = all interfaces
    server_address.sin_port = htons(port);          // Convert byte order

    if (bind(server_fd, (sockaddr*) &server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to bind socket." << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Bind socket successfully 0.0.0.0:" << port << std::endl;
    std::cout << "Listen on all network interfaces:" << std::endl;

    // ============================================
    // STEP 3: LISTEN - ready to accept connections
    // ============================================
    constexpr int backlog = 128;
    if (listen(server_fd, backlog) < 0) {
        std::cerr << "Failed to listen." << std::endl;
        close(server_fd);
        return 2;
    }

    std::cout << "✅ Server is listening (backlog: " << backlog << ")" << std::endl;
    std::cout << "   Ready to accept connections...\n" << std::endl;

    // ============================================
    // STEP 4: ACCEPT - Accept client connections
    // ============================================
    sockaddr_in client_address{};
    socklen_t client_address_size = sizeof(client_address);

    int client_fd = accept(server_fd, (sockaddr*) &client_address, &client_address_size);
    if (client_fd < 0) {
        std::cerr << "Failed to accept connection." << std::endl;
        close(server_fd);
        return 3;
    }

    //  Collect the client info
    char client_ip[client_address_size];
    inet_ntop(AF_INET, &client_address.sin_addr, client_ip, sizeof(client_ip));
    int client_port = ntohs(client_address.sin_port);

    std::cout << "✅ Client connected!" << std::endl;
    std::cout << "   Client IP:   " << client_ip << std::endl;
    std::cout << "   Client Port: " << client_port << std::endl;
    std::cout << "   Socket FD:   " << client_fd << "\n" << std::endl;

    // ============================================
    // STEP 5: RECEIVE - Receive data from client
    // ============================================
    while (true) {
        std::cout << "Waiting the data from client..." << std::endl;
        std::cout << "   (Blocking here till client sent)\n" << std::endl;

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));  // Clear buffer

        size_t bytes_recv = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv > 0) {
            buffer[bytes_recv] = '\0';
            std::cout << "✅ Received: " << bytes_recv << " bytes:" << std::endl;
            std::cout << "   Message: \"" << buffer << "\"\n" << std::endl;
        }
        else if (bytes_recv == 0) {
            std::cerr << "Connection closed." << std::endl;
        }
        else {
            std::cerr << "Failed to receive message." << std::endl;
        }

        if (strcmp(buffer,"quit") == 0 || strcmp(buffer,"exit") == 0) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
    }


    // ============================================
    // STEP 6: SEND - Send response for client
    // ============================================

    // std::cout << "Send response for client..." << std::endl;
    //
    // std::string response = "Server received: " + std::string(buffer);
    //
    // size_t bytes_sent = send(client_fd,
    //                          response.c_str(),
    //                          response.length(),
    //                          0);
    //
    // if (bytes_sent < 0) {
    //     std::cerr << "❌ Failed: Send failed" << std::endl;
    // } else {
    //     std::cout << "✅ Sent " << bytes_sent << " bytes" << std::endl;
    //     std::cout << "   Response: \"" << response << "\"\n" << std::endl;
    // }

    // ============================================
    // STEP 7: CLOSE - Close connections
    // ============================================
    std::cout << "Close connections..." << std::endl;

    close(client_fd);
    std::cout << "✅ Closed client socket" << std::endl;

    close(server_fd);
    std::cout << "✅ Closed server socket" << std::endl;

    std::cout << "\n=== SERVER STOPPED ===" << std::endl;

    return 0;
}