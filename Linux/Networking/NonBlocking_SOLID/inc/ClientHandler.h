//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_CLIENTHANDLER_H
#define EX01_CLIENTHANDLER_H
#include "IEventHandler.h"
#include "NetworkUtility.h"
#include "ThreadPool.h"

namespace networking {
    class ClientHandler : public IEventHandler {
    public:
        ClientHandler(ThreadPool& pool);
        void handle(int fd, event_t events) override;

    private:
        //  Inject to assign task inside handler => Use ref
        ThreadPool& pool_;
    };
}
#endif //EX01_CLIENTHANDLER_H