//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_IOBSERVER_H
#define EX01_IOBSERVER_H

namespace networking {
    enum class RoomEvent {
        JOIN = 0,
        LEAVE = 1,
        MESSAGE = 2
    };

    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void update(RoomEvent ev, std::string room, std::string source) = 0;
    };
}


#endif //EX01_IOBSERVER_H