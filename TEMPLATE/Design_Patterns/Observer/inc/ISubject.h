//
// Created by tuo8hc on 10/13/25.
//

#ifndef EX01_ISUBJECT_H
#define EX01_ISUBJECT_H
#include "IObserver.h"

#include <iostream>

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void notify() = 0;
    virtual void attach(IObserver *observer) = 0;
    virtual void deattach(IObserver *observer) = 0;
};

#endif //EX01_ISUBJECT_H