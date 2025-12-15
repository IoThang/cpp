//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_CLIENTHANDLER_H
#define EX01_CLIENTHANDLER_H
#include "IEventHandler.h"
#include "NetworkUtility.h"
#include "ThreadPool.h"
#include "ClientRegistry.h"
#include "ClientInfo.h"

namespace networking {
    class ClientHandler : public IEventHandler {
    public:
        ClientHandler(ThreadPool& pool, ClientRegistry& registry);
        void handle(int fd, event_t events) override;

        //  Helper method:
        std::vector<int> parseMsgAndLookUp(std::string& line);

    private:
        //  Inject to assign task inside handler => Use ref
        ThreadPool& pool_;
        //  Inject to get and lookup the name and room
        ClientRegistry& registry_;
    };
}
#endif //EX01_CLIENTHANDLER_H