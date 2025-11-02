//
// Created by TUO8HC on 10/6/2025.
//

#include "../inc/Concurrent_Queue.h"

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



