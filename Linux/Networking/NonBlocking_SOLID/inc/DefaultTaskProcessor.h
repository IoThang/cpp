//
// Created by tuo8hc on 10/29/25.
//

#ifndef EX01_DEFAULTTASKPROCESSOR_H
#define EX01_DEFAULTTASKPROCESSOR_H
#include <shared_mutex>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "ClientInfoFactory.h"
#include "ClientRegistry.h"
#include "Task.h"
#include "NetworkUtility.h"

namespace networking {
    class ITaskProcessor {
    public:
        virtual ~ITaskProcessor() = default;
        //  Pass by ref, since copy ctor is deleted
        virtual void process(const Task& task) = 0;
    };
}

namespace networking {
    class DefaultTaskProcessor : public ITaskProcessor {
    public:
        explicit DefaultTaskProcessor(ClientRegistry& registry);
        //  Pass by ref, since copy ctor is deleted
        void process(const Task& task) override;
    private:
        // Thread-safe access
        std::shared_mutex mutable clients_mutex;
        //  Injected
        ClientRegistry& registry_;
    };
}



#endif //EX01_DEFAULTTASKPROCESSOR_H