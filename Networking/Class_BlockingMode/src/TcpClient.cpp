//
// Created by TUO8HC on 10/9/2025.
//

#include "../inc/TcpClient.h"

TcpClient::TcpClient(std::string const &ip, int const port) : clientSocket_(INVALID_SOCKET), serverIp_(ip), port_(port), initialized_(false) {
    WSAData WsaData;
    if (WSAStartup(MAKEWORD(2,2), &WsaData) != 0) {
        std::cerr << "Failed to initialize WSAData!" << std::endl;
        return;
    }
    initialized_ = true;

    clientSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket_ == INVALID_SOCKET) {
        std::cerr << "Failed to create socket!" << WSAGetLastError() << std::endl;
        WSACleanup();
        initialized_ = false;
        return;
    }
    std::cout << "Client socket created for" << ip << ":" << port << std::endl;
}

bool TcpClient::connectToServer() {
    if (!initialized_ || clientSocket_ == INVALID_SOCKET) {
        std::cerr << "Client not initialized properly!" << std::endl;
        return false;
    }

    //  Establish server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_); //  Network byte order

    //  Convert IP string to binary (IPv4)
    if (inet_pton(AF_INET, serverIp_.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid ip address: " << serverIp_ << std::endl;
    }

    //  Connect: blocking, wait server to accept
    if (connect(clientSocket_, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect!" << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Connected to server " << serverIp_ << " : " << port_ << std::endl;
    return true;
}


//  Send message: similar to server
bool TcpClient::sendMessage(std::string const &message) {
    if (clientSocket_ == INVALID_SOCKET) {
        std::cerr << "Not connected!" << std::endl;
        return false;
    }

    int result = send(clientSocket_, message.c_str(), message.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to send message!" << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "Sent message: " << message << std::endl;
    return true;
}

//  Receive message: Similar to server
std::string TcpClient::receiveMessage() {
    if (clientSocket_ == INVALID_SOCKET) {
        std::cerr << "Not connected!" << std::endl;
        return "";
    }

    char buffer[1024] = {0};
    int result = recv(clientSocket_, buffer, 1024, 0);
    if (result > 0) {
        std::string msg(buffer);
        std::cout << "Received message: " << msg << std::endl;
        return msg;
    }
    else if (result == 0) {
        std::cerr << "Server disconnected!" << std::endl;
    }
    else {
        std::cerr << "Failed to receive message!" << WSAGetLastError() << std::endl;
    }

    closesocket(clientSocket_);
    clientSocket_ = INVALID_SOCKET;
    return "";
}

bool TcpClient::isConnected() const {
    return clientSocket_ != INVALID_SOCKET;
}

TcpClient::~TcpClient() {
    if (clientSocket_ != INVALID_SOCKET) {
        closesocket(clientSocket_);
        clientSocket_ = INVALID_SOCKET;
    }
    if (initialized_) {
        WSACleanup();
    }
}


