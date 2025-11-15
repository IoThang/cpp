//
// Created by TUO8HC on 10/6/2025.
//

#ifndef EX01_CONCURRENT_QUEUE_H
#define EX01_CONCURRENT_QUEUE_H

#include <queue>
#include <condition_variable>
#include <optional>
#include <mutex>

template <typename T>
class Concurrent_Queue {
public:
    Concurrent_Queue() = default;
    Concurrent_Queue(Concurrent_Queue const&) = delete;
    Concurrent_Queue &operator=(Concurrent_Queue const&) = delete;

    // push rvalue / lvalue
    void push(T item);
    std::optional<T> wait_and_pop();
    std::optional<T> try_pop();
    void close();
    bool empty() const;
    [[nodiscard]] size_t size() const;
private:
    std::queue<T> queue_;
    std::mutex mutable mutex_;
    std::condition_variable cv_;
    bool close_ = false; //  To safely stop
};

template<typename T>
void Concurrent_Queue<T>::push(T item) {
    {
        std::lock_guard<std::mutex> lck(mutex_);
        if (close_)
            throw std::runtime_error("Can't push to queue when waiting push");
        queue_.push(std::move(item));
    }   // ~lck: for safe unlocking
    cv_.notify_one(); // New data is available => Wake-up consumer
}

// Blocking pop: return optional<T>, nullopt if queue closes and empty
template<typename T>
std::optional<T> Concurrent_Queue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lck(mutex_);
    //  Wait till the data available or queue is closed
    cv_.wait(lck, [&]{ return (!queue_.empty() || close_); });

    if (queue_.empty())
        //  Close and empty
            return std::nullopt;
    T item = std::move(queue_.front());
    queue_.pop();
    return item;
}

//  Non-blocking pop
template<typename T>
std::optional<T> Concurrent_Queue<T>::try_pop() {
    std::unique_lock<std::mutex> lck(mutex_);
    if (queue_.empty())
        return std::nullopt;
    T item = std::move(queue_.front());
    queue_.pop();
    return item;
}

//  Close queue:
template<typename T>
void Concurrent_Queue<T>::close() {
    {
        std::lock_guard<std::mutex> lck(mutex_);
        close_ = true;
    }
    //  Waku up all consumer to close
    cv_.notify_all();
}

template<typename T>
bool Concurrent_Queue<T>::empty() const {
    std::lock_guard<std::mutex> lck(mutex_);
    return queue_.empty();
}

template<typename T>
size_t Concurrent_Queue<T>::size() const {
    std::lock_guard<std::mutex> lck(mutex_);
    return queue_.size();
}


#endif //EX01_CONCURRENT_QUEUE_H