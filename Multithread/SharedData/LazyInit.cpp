//
// Created by TUO8HC on 10/1/2025.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Global mutex object
std::mutex m1, m2;

/* Deadlock example
void task1() {
    std::lock_guard<std::mutex> lk1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::lock_guard<std::mutex> lk2(m2);
    std::cout << "Task 1 done\n";
}

void task2() {
    std::lock_guard<std::mutex> lk2(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::lock_guard<std::mutex> lk1(m1);
    std::cout << "Task 2 done\n";
}
*/

/* std::scoped_lock */
void task1(int id) {
    std::cout << "Thread " << id << " starts\n";
    {
        //  In critical section: both mutexes are locked
        std::scoped_lock lk1(m1, m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Thread " << id << " is in critical section\n";
    }   //  Calling ~std::scope_lock to unlock
    //  Out scope: Both mutexes already unlocked
    std::cout << "Thread " << id << " outside critical section\n";
    std::cout << "Task 1 done\n";
}

void task2(int id) {
    std::cout << "Thread " << id << " starts\n";
    {
        //  In critical section: both mutexes are locked
        std::scoped_lock lck2(m2, m1);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } //  Calling ~std::scope_lock to unlock
    //  Out scope: Both mutexes already unlocked
    std::cout << "Thread " << id << " outside critical section\n";
    std::cout << "Task 2 done\n";
}


int main(
    int argc, char *argv[]) {

    std::thread thr1(task1, 0);
    std::thread thr2(task2, 1);

    thr1.join();
    thr2.join();

    return 0;
}