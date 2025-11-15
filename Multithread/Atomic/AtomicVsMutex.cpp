//
// Created by TUO8HC on 10/4/2025.
//
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

std::mutex mtx;
std::atomic_flag spin = ATOMIC_FLAG_INIT;
int counter = 0;

void test_mutex() {
    for (int i = 0; i < 1'000'000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

void test_spin() {
    for (int i = 0; i < 1'000'000; ++i) {
        while (spin.test_and_set(std::memory_order_acquire)) {}
        // spin
        ++counter;
        spin.clear(std::memory_order_release);
    }
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::thread a(test_mutex), b(test_mutex);
    a.join(); b.join();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Mutex time: " << std::chrono::duration<double>(t2-t1).count() << "s\n";

    counter = 0;
    auto t3 = std::chrono::high_resolution_clock::now();
    std::thread c(test_spin), d(test_spin);
    c.join(); d.join();
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Spin time: " << std::chrono::duration<double>(t4-t3).count() << "s\n";
}
