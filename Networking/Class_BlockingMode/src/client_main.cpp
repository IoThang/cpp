//
// Created by TUO8HC on 10/9/2025.
//

#include "../inc/TcpClient.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string ip = "127.0.0.1";
    unsigned short port = 8080;
    if (argc > 1) {
        ip = argv[1];
    }
    if (argc > 2) {
        try {
            port = std::stoi(argv[2]);
        }
        catch (...) {
            std::cerr << "Invalid port" << argv[2] << std::endl;
            return 1;
        }
    }
    std::cout <<"Connecting to " << ip << " : " << port << std::endl;

    TcpClient client(ip, port);
    if (!client.connectToServer()) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    std::cout << "Connected! Chat loop started" << std::endl;
    std::string message;
    while (true) {
        // Bước 1: Nhập từ console
        std::cout << "Client (>): ";  // Prompt
        std::getline(std::cin, message);  // Lấy cả dòng
        if (message == "quit" || message == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        if (message.empty()) continue;  // Bỏ qua nếu rỗng

        // Bước 2: Gửi message
        if (!client.sendMessage(message)) {
            std::cerr << "Failed to send message!" << std::endl;
            break;
        }

        // Bước 3: Nhận phản hồi (blocking, chờ server gửi)
        // std::string received = client.receiveMessage();
        // if (!received.empty()) {
        //     std::cout << "Server: " << received << std::endl;  // In phản hồi
        // } else {
        //     // Nếu empty, server disconnect
        //     std::cout << "Server disconnected. Exiting..." << std::endl;
        //     break;
        // }
    }

    //  Close connected
    if (client.isConnected()) {
        client.sendMessage("Client disconnected.");  // Thông báo (tùy chọn)
    }

    return 0;
}