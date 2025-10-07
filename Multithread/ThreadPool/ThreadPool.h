//
// Created by TUO8HC on 10/7/2025.
//

#ifndef QUEUE_THREADPOOL_H
#define QUEUE_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(size_t nThreads);
    //  Disallow copy
    ThreadPool(ThreadPool const&) = delete;
    ThreadPool &operator=(ThreadPool const&) = delete;
    ~ThreadPool() noexcept;

    // Graceful shutdown: finish queued tasks then stop
    void shutdown();

    // Immediate shutdown (best-effort): won't wait tasks finish
    // Note: not safe to forcefully terminate threads in C++, so not implemented here.
    // Provide query helpers:
    size_t threadCount() const noexcept;
    size_t queuedTaskCount() const noexcept;
    size_t activeTaskCount() const noexcept;

    // Submit a task, return future
    template<class F, class ... Args>
    auto submit(F &&f, Args &&... args) -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutable mutex_;
    std::condition_variable cv_;
    std::atomic<size_t> activeTasks_{0};
    bool stop_ = false;

    void workerLoop();
};

template<typename F, typename... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result_t<F, Args...>>
{
    using ReturnType = typename std::invoke_result_t<F, Args...>;
    auto taskPtr = std::make_shared<std::packaged_task<ReturnType()>>(
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<ReturnType> res = taskPtr->get_future();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stop_) throw std::runtime_error("submit on stopped ThreadPool");
        tasks_.emplace([taskPtr](){
            (*taskPtr)();
        });
    }
    cv_.notify_one();
    return res;
}

#endif //QUEUE_THREADPOOL_H
