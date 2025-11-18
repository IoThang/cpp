//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_CLIENTHANDLER_H
#define EX01_CLIENTHANDLER_H
#include "IEventHandler.h"
#include "../inc/NetworkUtility.h"

namespace networking {
    class ClientHandler : public IEventHandler {
    public:
        void handle(int fd, event_t events) override;
    };
}
#endif //EX01_CLIENTHANDLER_H