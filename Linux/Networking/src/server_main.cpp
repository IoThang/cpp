//
// Created by tuo8hc on 10/11/25.
//

#include "SocketFactory.h"
#include "Server.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    int port = std::stoi(argv[1]);
    try {
        auto socket = SocketFactory::create();
        Server server(port, std::move(socket));
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}