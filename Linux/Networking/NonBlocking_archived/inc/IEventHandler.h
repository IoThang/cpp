//
// Created by tuo8hc on 10/14/25.
//

#ifndef EX01_IEVENTHANDLER_H
#define EX01_IEVENTHANDLER_H

#include <stdint.h>

class IEventHandler {
public:
    virtual ~IEventHandler() = default;
    virtual void handleEvent(int fd, uint32_t events);
};

#endif //EX01_IEVENTHANDLER_H