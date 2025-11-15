//
// Created by tuo8hc on 10/11/25.
//

#include "SocketFactory.h"
#include "client.h"
#include <iostream>



int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }
    std::string host = argv[1];
    int port = std::stoi(argv[2]);
    try {
        auto socket = SocketFactory::create();
        Client client(std::move(socket));
        client.connect(host, port);
        client.send("Hello Server!");
        std::string response = client.recv();
        std::cout << "Response: " << response << std::endl;
        client.close();
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}