//
// Created by tuo8hc on 10/11/25.
//

#include "../inc/client.h"
class Client {
private:
    std::unique_ptr<ISocket> socket_;

public:
    Client(std::unique_ptr<ISocket> socket) : socket_(std::move(socket)) {}

    void connect(const std::string& host, int port) {
        if (socket_->connect(host, port) < 0) {
            throw std::runtime_error("Connect failed");
        }
    }

    void send(const std::string& msg) {
        socket_->send(msg);  // Blocking send nếu buffer full
    }

    std::string recv() {
        std::string buf;
        socket_->recv(buf);  // Blocking recv
        return buf;
    }

    void close() {
        socket_->close();
    }
};