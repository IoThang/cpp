//
// Created by TUO8HC on 10/6/2025.
//

#include "../inc/Concurrent_Queue.h"
#include <iostream>
#include <thread>
#include "../../../shared_lib/timer.hpp"

// void producer(int id, int count)
// {
//     for (int i = 0; i < count; ++i) {
//         q.push(id * 1000 + i);
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//     }
// }
//
// void consumer(int id) {
//     while (true) {
//         auto v = q.wait_and_pop();
//         if (!v) break; // queue closed and empty
//         std::cout << "Consumer " << id << " got " << *v << "\n";
//     }
//     std::cout << "Consumer " << id << " exiting\n";
// }

int main() {
    Timer t("Main");
    Concurrent_Queue<int> q;
    // producers
    auto producer = [&](int id, int count) {
        for (int i = 0; i < count; ++i) {
            q.push(id * 1000 + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };

    // consumers
    auto consumer = [&](int id) {
        while (true) {
            auto v = q.wait_and_pop();
            if (!v) break; // queue closed and empty
            std::cout << "Consumer " << id << " got " << *v << "\n";
        }
        std::cout << "Consumer " << id << " exiting\n";
    };

    std::thread p1(producer, 1, 10);
    std::thread p2(producer, 2, 10);

    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join();
    p2.join();

    q.close(); // thông báo producers xong -> wake consumers

    c1.join();
    c2.join();

    return 0;
}