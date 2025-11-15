//
// Created by tuo8hc on 10/31/25.
//

#include "../inc/ThreadPool.h"

// Ctor: Spawn N workers, inject processor
networking::ThreadPool::ThreadPool(size_t num_threads, std::unique_ptr<ITaskProcessor> proc) : processor_(std::move(proc)), num_threads_(num_threads) {
    if (num_threads == 0) {
        num_threads_ = std::thread::hardware_concurrency();
    }

    for (auto i = 0; i < num_threads; i++) {
        threads_.emplace_back([this] {workerLoop(); });
        std::cout << "[ThreadPool] Started with " << num_threads_ << " workers" << std::endl;
    }
}

networking::ThreadPool::~ThreadPool() {
    stop_ = true;
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        // Clear queue to avoid processing during shutdown
        while (!task_queue_.empty()) {
            task_queue_.pop();
        }
    }
    // Wake workers for shutdown
    cv_.notify_all();
    // Thread wrappers auto-join in their dtors (RAII)
}
// Enqueue task (thread-safe)
void networking::ThreadPool::enqueue(Task task) {
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        task_queue_.push(std::move(task));
    }
    cv_.notify_one();
}

void networking::ThreadPool::workerLoop() {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            cv_.wait(lock, [this] { return stop_ || !task_queue_.empty(); });
            if (stop_ && task_queue_.empty()) return;
            task = std::move(task_queue_.front());
            task_queue_.pop();
        }
        if (processor_) {
            processor_->process(task);
        }
    }
}