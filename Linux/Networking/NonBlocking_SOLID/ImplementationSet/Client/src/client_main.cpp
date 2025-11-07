//
// Created by tuo8hc on 10/24/25.
//

#include "EpollClient.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 3) {
        std::cerr << "Too much arg" << std::endl;
    }
    std::string hostname = argv[1];
    int port = std::stoi(argv[2]);

    try {
        networking::EpollClient client(hostname, port);
        client.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}