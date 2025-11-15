//
// Created by TUO8HC on 10/8/2025.
//

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urbi.lib")

int main() {
    WSAData wsaData;
    int result = WSAStartup(MAKEWORD(2,2),&wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    //  Create socket
    SOCKET server_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "socket() failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(server_fd,(SOCKADDR*)&server_addr,sizeof(server_addr)) != 0) {
        std::cerr << "connect() failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    const char* message = "Hello from client";
    send(server_fd, message, strlen(message), 0);

    char buffer[1024] = {0};
    recv(server_fd, buffer, 1024, 0);
    std::cout << buffer << std::endl;
    return 0;
}