//
// Created by TUO8HC on 10/1/2025.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Global mutex object
std::mutex mut;

//  Example how to use mutex
void print(std::string const& msg) {
    for (int i = 0; i < 5; i++) {
        //  Lock mutex before going CS
        mut.lock();
        std::cout << msg[0] << msg[1] << msg[2] << std::endl;
        //  Unlock mutex after leaving CS
        mut.unlock();
    }
}

//  Try_lock member function: example
void task1() {
    std::cout << "Task1 is trying to lock the mutex" << std::endl;
    mut.lock();
    std::cout << "Task1 is locked" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Task1 is unlocked" << std::endl;
    mut.unlock();
}

void task2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Task2 is trying to lock the mutex" << std::endl;
    while (!mut.try_lock()) {
        std::cout << "Task2 is not locked" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Task2 is locked" << std::endl;
    std::cout << "Task2 is unlocked" << std::endl;
    mut.unlock();
}

int main(
    int argc, char *argv[]) {


    // std::thread thr1(print,"abc");
    // std::thread thr2(print,"def");
    // std::thread thr3(print,"xyz");

    std::thread thr4(task1);
    std::thread thr5(task2);


    // thr1.join();
    // thr2.join();
    // thr3.join();

    thr4.join();
    thr5.join();

    return 0;
}