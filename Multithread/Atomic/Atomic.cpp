//
// Created by TUO8HC on 10/5/2025.
//

#include "../../shared_lib/timer.hpp"

#include <atomic>
#include <thread>
#include <vector>

#define ATOMIC_BASIC 0
#define SPIN_LOCK    1
#define PRACTICE    SPIN_LOCK

#if PRACTICE == ATOMIC_BASIC
std::atomic<int> counter{0};

//  Atomic counter cơ bản
void increment() {
    Timer t("atomic task");
    for (int i = 0; i < 1'000'000; ++i)
        ++counter;
}
#endif

#if PRACTICE == SPIN_LOCK
std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
int shared_data = 0;

void increment() {
    Timer t("atomic task for spinlock");
    for (int i = 0; i < 100000; ++i) {
        while (lock_flag.test_and_set(std::memory_order_acquire)) {}
        // spin
        ++shared_data;
        lock_flag.clear(std::memory_order_release);
    }
}
#endif

int main() {
    Timer time("Main");

    constexpr int thread_count = 5;
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

#if PRACTICE == ATOMIC_BASIC
    for (int i = 0; i < thread_count; ++i)
        threads.emplace_back(increment);

    for (auto& t : threads) t.join();
    std::cout << "Final counter = " << counter << '\n';
#endif


#if PRACTICE == SPIN_LOCK
    for (int i = 0; i < thread_count; ++i)
        threads.emplace_back(increment);

    for (auto& t : threads) t.join();
    std::cout << "Final share data = " << shared_data << '\n';
#endif

    return 0;
}