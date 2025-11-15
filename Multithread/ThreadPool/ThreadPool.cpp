//
// Created by TUO8HC on 10/7/2025.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t nThreads) {
    if (nThreads == 0) {
        nThreads = 1;
    }
    for (size_t i = 0; i < nThreads; i++) {
        workers_.emplace_back([this] {
            workerLoop();
        });
    }
}

ThreadPool::~ThreadPool() noexcept {
    shutdown();
}

void ThreadPool::shutdown() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stop_) return; // idempotent
        stop_ = true;
    }
    cv_.notify_all();
    for (std::thread &worker : workers_) {
        if (worker.joinable()) worker.join();
    }
}

size_t ThreadPool::threadCount() const noexcept {
    return workers_.size();
}

size_t ThreadPool::queuedTaskCount() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return tasks_.size();
}

size_t ThreadPool::activeTaskCount() const noexcept {
    return activeTasks_.load();
}

void ThreadPool::workerLoop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [&] {return stop_ || !tasks_.empty(); });
            if (stop_ && tasks_.empty()) return;

            task = std::move(tasks_.front());
            tasks_.pop();
            activeTasks_.fetch_add(1, std::memory_order_relaxed);
        }

    // Execute outside the lock
    try {
        task();
    } catch (...) {
        // packaged_task will store exception, so rethrowing not needed here
    }
    activeTasks_.fetch_sub(1, std::memory_order_relaxed);
    }
}
