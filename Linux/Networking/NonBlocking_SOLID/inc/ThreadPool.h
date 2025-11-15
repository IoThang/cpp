//
// Created by tuo8hc on 10/31/25.
//

#ifndef EX01_THREADPOOL_H
#define EX01_THREADPOOL_H

#include <iostream>
#include <condition_variable>
#include <vector>
#include <queue>
#include <mutex>
#include <shared_mutex>

#include "DefaultTaskProcessor.h"
#include "Task.h"
#include "Thread.h"

namespace networking {
    class ThreadPool {
    public:
        explicit ThreadPool(size_t num_threads, std::unique_ptr<ITaskProcessor> proc);
        ~ThreadPool();

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;


        void enqueue(Task task);
    private:
        std::vector<Thread> threads_;
        std::queue<Task> task_queue_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;
        std::unique_ptr<ITaskProcessor> processor_;
        bool stop_ = false;
        size_t num_threads_;

        void workerLoop();
    };
}



#endif //EX01_THREADPOOL_H