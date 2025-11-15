//
// Created by TUO8HC on 10/5/2025.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

class Timer {
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::string task_name_;
public:
    explicit Timer(std::string task_name_) : start_(std::chrono::steady_clock::now()), task_name_(std::move(task_name_)) {}
    ~Timer() {
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
        std::cout << "Task "<< task_name_ << " elapsed: " << ms << " ms\n";
    }
};

void heavy_task() {
    Timer t(std::move("heavy_task"));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void worker(int id) {
    Timer t(std::move("thread" + std::to_string(id)));
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id)); // giả lập công việc

}

int main() {
    Timer myTimer(std::move("Main thread"));

    heavy_task();   // Giả lập task nặng

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join(); t2.join(); t3.join();

    return 0;
}
