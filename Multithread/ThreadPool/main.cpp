//
// Created by TUO8HC on 10/7/2025.
//

#include <iostream>
#include "ThreadPool.h"
#include "../../shared_lib/timer.hpp"

int main() {
    Timer t("Main");
    ThreadPool pool(std::thread::hardware_concurrency());

    // submit a simple task returning int
    auto fut1 = pool.submit([](int a, int b) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return a + b;
    }, 2, 3);

    // submit many tasks
    std::vector<std::future<int>> results;
    for (int i = 0; i < 1000; ++i) {
        results.emplace_back(
            pool.submit([i] { return i * i; })
        );
    }

    std::cout << "fut1 = " << fut1.get() << "\n";
    for (auto &f : results) {
        std::cout << f.get() << " ";
    }
    std::cout << "\n";

    pool.shutdown();
    return 0;
}