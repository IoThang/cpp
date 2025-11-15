//
// Created by TUO8HC on 10/9/2025.
//

#include "../inc/TcpServer.h"
#include <windows.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    int portNumber = 8080;
    if (argc > 1) {
        try {
            //  Convert string to int, throw if invalid
            portNumber = std::stoi(argv[1]);
        }
        catch (...) {
            std::cerr << "Invalid argument: " << argv[1] << std::endl;
        }
    }

    std::cout << "Starting server on port : " << portNumber << std::endl;

    //  Create instance
    TcpServer server(portNumber);
    //  Start listen and accept
    if (!server.start()) {
        std::cerr << "Server failed to start" << std::endl;
        return 1;
    }

    std::cout << "Connected! Chat loop started" << std::endl;
    std::string message;
    while (true) {
        //  Receive message from client (blocking if no data)
        std::string received = server.receiveMessage();
        if (!received.empty()) {
            std::cout <<"Server received: " << received << std::endl;
        }
        else {
            // if empty, client disconnected or issue
            std::cout << "Client disconnected. Exiting..." << std::endl;
            break;
        }

        // std::cout << "Server (>): ";  // Prompt
        // std::getline(std::cin, message);  // Dùng getline để lấy cả dòng, bao gồm space
        // if (message == "quit" || message == "exit") {
        //     std::cout << "Goodbye!" << std::endl;
        //     break;
        // }
        // if (!message.empty()) {  // Chỉ gửi nếu không rỗng
        //     if (!server.sendMessage(message)) {
        //         std::cerr << "Failed to send message!" << std::endl;
        //         break;
        //     }
        // }
    }

    // Wait client to receive (optional, but avoid to close immediately)
    Sleep(1000);
    if (server.isConnected()) {
        server.sendMessage("Server disconnected.");  // Thông báo trước khi đóng (tùy chọn)
    }

    return 0;
}