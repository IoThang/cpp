//
// Created by tuo8hc on 10/13/25.
//

#ifndef EX01_IOBSERVER_H
#define EX01_IOBSERVER_H

#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(std::string const& msg_from_subject) = 0;
};

#endif //EX01_IOBSERVER_H