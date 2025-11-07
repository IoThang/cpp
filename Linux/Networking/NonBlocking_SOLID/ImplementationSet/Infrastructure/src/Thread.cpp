//
// Created by tuo8hc on 10/31/25.
//

#include "../inc/Thread.h"

networking::Thread::Thread(std::function<void()> callback){
    thread_ = std::thread(std::move(callback));
    if (!thread_.joinable()) {
        throw std::runtime_error("[ERROR] thread creation failed");
    }
}

networking::Thread::Thread(Thread&& other) {
    if (this != &other) {
        join();
        thread_ = std::move(other.thread_);
        joined_ = other.joined_;
        other.joined_ = true;
    }
}

networking::Thread &networking::Thread::operator=(Thread && other)  {
    if (this != &other) {
        join();
        thread_ = std::move(other.thread_);
        joined_ = other.joined_;
        other.joined_ = true;
    }
    return *this;
}

networking::Thread::~Thread() noexcept {
    join();
}

void networking::Thread::join() {
    if (!joined_ && thread_.joinable()) {
        thread_.join();
    }
    joined_ = true;
}
