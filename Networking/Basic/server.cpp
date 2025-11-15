//
// Created by TUO8HC on 10/8/2025.
//

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSAData wsaData{};
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

    //  Establish address and bind
    SOCKADDR_IN address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8000);

    if (bind(server_fd,(SOCKADDR*)&address,sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    //  Listen for connection
    if (listen(server_fd,5) == SOCKET_ERROR) {
        std::cerr << "listen() failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    SOCKET new_socket = accept(server_fd,(SOCKADDR*)&address,NULL);
    if (new_socket == INVALID_SOCKET) {
        std::cerr << "accept() failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    //  Send and receive data
    char buffer[1024] = {0};
    int valread = recv(new_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Data from client: " << buffer << std::endl;
    }

    const char* hello = "Hello from server!";
    send(new_socket, hello, strlen(hello), 0);

    //  Close socket and clean up
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
}
