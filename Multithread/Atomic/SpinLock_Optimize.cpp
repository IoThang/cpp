//
// Created by TUO8HC on 10/5/2025.
//

#include "../../shared_lib/timer.hpp"
#include <thread>
#include <atomic>
#include <vector>

int shared_data = 0;

class SpinLock {
public:
    // Optimize: Backoff strategy (giảm tải CPU khi spin quá lâu):
    void lock() {
        int attempt = 0;
        // while true nếu flag đã set thì tiếp tục spin
        while (lock_flag_.test_and_set(std::memory_order_acquire)) {
            if (++attempt % 100 == 0)
                std::this_thread::yield(); // nhường CPU tạm thời
            // busy wait
        }
    }

    void unlock() {
        lock_flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag lock_flag_ = ATOMIC_FLAG_INIT;
};

//  A wrapper class to unlock safety (using RAII)
class SpinLock_Guard {
public:
    explicit SpinLock_Guard(SpinLock& lock): lock_(lock) {
        lock_.lock();
    }
    ~SpinLock_Guard() {
        lock_.unlock();
    }
private:
    SpinLock& lock_;
};

SpinLock spin_lock;

void task() {
    Timer t("atomic task for spinlock");
    for (int i = 0; i < 100000; ++i) {
        SpinLock_Guard lock_guard(spin_lock);
        // spin
        ++shared_data;
    } // call ~SpinLock_Guard, RAII để tự động unlock khi ra khỏi scope
}

int main() {
    Timer time("Main");

    constexpr int thread_count = 5;
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int i = 0; i < thread_count; ++i)
        threads.emplace_back(task);

    for (auto& t : threads) t.join();
    std::cout << "Final share data = " << shared_data << '\n';

    return 0;
}