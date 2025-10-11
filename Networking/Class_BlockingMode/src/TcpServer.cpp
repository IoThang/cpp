//
// Created by TUO8HC on 10/9/2025.
//

#include "../inc/TcpServer.h"

//  Constructing params (IP/port), calling WSAStartup
TcpServer::TcpServer(int const port) : server_fd_(INVALID_SOCKET), client_fd_(INVALID_SOCKET), port_(port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "Can't start Winsock!" << std::endl;
        return;
    }
    initialized_ = true;

    server_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == server_fd_) {
        std::cerr << "Can't create socket!" << std::endl;
        WSACleanup();
        initialized_ = false;
        return;
    }
}

//  Bind, listen, accept for single client
bool TcpServer::start() {
    if (!initialized_ || server_fd_ == INVALID_SOCKET) {
        std::cerr << "Server not initialized properly!" << std::endl;
        return false;
    }

    sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    //  Bind socket into IP/Port
    if (bind(server_fd_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0) {
        std::cerr << "Bind failed!" << WSAGetLastError() << std::endl;
        return false;
    }

    //  Listen with 3 backlog (the maximum number which is waiting to connect)
    if (listen(server_fd_, 5) != 0) {
        std::cerr << "Listen failed!" << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Server listening on port" << port_ << " (Wait client ...)" << std::endl;

    //  Accept blocking: Wait client to connect, return new socket
    client_fd_ = accept(server_fd_, (sockaddr*)&address, &addrlen);
    if (client_fd_ == INVALID_SOCKET) {
        std::cerr << "Accept failed!" << WSAGetLastError() << std::endl;
        return false;
    }

    //  Print IP client
    std::cout << "Client connected from" << inet_ntoa(address.sin_addr) << std::endl;
    return true;
}

//  Send msg: call send() with string arg
bool TcpServer::sendMessage(std::string message) {
    if (client_fd_ == INVALID_SOCKET) {
        std::cerr << "No client connected - Can not send" << std::endl;
        return false;
    }

    //  Send(): Send byte from message.c_str(), length is size of string (except NULL terminator)
    int result = send(client_fd_, message.c_str(), static_cast<int>(message.length()), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed!" << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "Sent " << result << std::endl;

    return true;
}

//  Receive message: recv() call with buffer fixed size
std::string TcpServer::receiveMessage() {
    if (client_fd_ == INVALID_SOCKET) {
        return "";
    }

    // Buffer 1KB, init 0 to avoid garbage value
    char buffer[1024] = {0};
    //  Recv(): Blocking, return the received bytes
    int valread = recv(client_fd_, buffer, 1024, 0);

    if (valread > 0) {
        //  Convert char[] to string (strip NULL terminator)
        std::string msg(buffer);
        std::cout << "Received: " << msg << std::endl;
        return msg;
    }
    else if (valread == 0) {
        std::cout << "Client disconnected gracefully!" << std::endl;
    }
    else {
        std::cerr << "Receive failed!" << WSAGetLastError() << std::endl;
    }
    // Close client socket if failed/disconnected
    closesocket(client_fd_);
    client_fd_ = INVALID_SOCKET;
    return "";
}

bool TcpServer::isConnected() const {
    return client_fd_ != INVALID_SOCKET;
}

TcpServer::~TcpServer() {
    //  Clean client socket
    if (client_fd_ != INVALID_SOCKET) {
        closesocket(client_fd_);
        client_fd_ = INVALID_SOCKET;
    }
    //  Clean server socket
    if (server_fd_ != INVALID_SOCKET) {
        closesocket(server_fd_);
        server_fd_ = INVALID_SOCKET;
    }
    //  Clean winsock
    if (initialized_) {
        WSACleanup();
    }
}
