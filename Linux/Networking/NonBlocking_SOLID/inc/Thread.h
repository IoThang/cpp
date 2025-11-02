//
// Created by tuo8hc on 10/31/25.
//

#ifndef EX01_THREAD_H
#define EX01_THREAD_H
#include <functional>
#include <thread>

namespace networking {
    class Thread {
    public:
        explicit Thread(std::function<void()> callback);
        ~Thread() noexcept;
        //  Disable copy
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        //  Allow move
        Thread(Thread&&);
        Thread& operator=(Thread&&);

        void join();
        bool joinable() const { return thread_.joinable(); };
    private:
        std::thread thread_;
        bool joined_{false};
    };
}



#endif //EX01_THREAD_H