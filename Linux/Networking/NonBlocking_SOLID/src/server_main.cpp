//
// Created by tuo8hc on 10/21/25.
//

#include <stdlib.h>
#include "EpollServer.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cerr << "Over arg" << std::endl;
    }
    int port = std::stoi(argv[1]);

    try {
        networking::EpollServer server(port);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
