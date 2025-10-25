//
// Created by tuo8hc on 10/18/25.
//

#include <stdlib.h>
#include "EchoServer.h"

int main(int argc, char* argv[]) {
    int port = std::stoi(argv[1]);
    try {
        EchoServer server;
        server.Start(port);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}