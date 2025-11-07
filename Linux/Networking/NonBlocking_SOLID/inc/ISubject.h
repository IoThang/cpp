//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_ISUBJECT_H
#define EX01_ISUBJECT_H

#include <memory>
#include "IObserver.h"

namespace networking {
/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */
    class ISubject {
    public:
        virtual ~ISubject() = default;

        virtual void attach(std::shared_ptr<IObserver> obs, std::string room) = 0;
        virtual void detach(std::shared_ptr<IObserver> obs, std::string room) = 0;
        virtual void notify(std::shared_ptr<IObserver> obs, std::string room) = 0;
    }
}


#endif //EX01_ISUBJECT_H