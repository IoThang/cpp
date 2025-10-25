//
// Created by tuo8hc on 10/22/25.
//

#ifndef EX01_IEVENTHANDLER_H
#define EX01_IEVENTHANDLER_H
#include <cstdint>

namespace networking {
    using event_t = uint32_t;

    class IEventHandler {
    public:
        virtual ~IEventHandler() = default;
        virtual void handle(int fd, event_t events) = 0;
    };
}

#endif //EX01_IEVENTHANDLER_H