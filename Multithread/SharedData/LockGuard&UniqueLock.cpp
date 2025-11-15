//
// Created by TUO8HC on 10/1/2025.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Global mutex object
std::mutex mut;

// ======================== Lock_Guard example ==============================
// void print(std::string const& msg) {
//     for (int i = 0; i < 5; i++) {
//         try {
//             // Create lock_guard object
//             // This also call lck_guard.lock() by default constructor of lock_guard class
//             std::lock_guard<std::mutex> lck_guard(mut);
//             std::cout << "\n mut is locked by lock guard" << std::endl;
//             // Start of CS
//             std::cout << msg[0] << msg[1] << msg[2] << std::endl;
//             // CS Throw an exception
//             // Expected output: mut already unlocked by lock guard, since the default deconstructor will call unlock mut => No hang the program
//             throw std::exception();
//             // End of CS
//         } // Call ~std::lock_guard
//         catch (std::exception& e) {
//             std::cout << "Exception caught:" << e.what() << std::endl;
//         }
//     }
// }

// ========================= Unique lock example ===========================
void print(std::string const& msg) {
    for (int i = 0; i < 5; i++) {
        // Create lock_guard object
        // This also call unique_lock.lock() by default constructor of unique_lock class
        std::unique_lock<std::mutex> unique_lck(mut);
        std::cout << "\n mut is locked by unique lock" << std::endl;
        // Start of CS
        std::cout << msg[0] << msg[1] << msg[2] << std::endl;
        // Unlock the mutex
        std::cout << "\n mut is unlocked by unique lock" << std::endl;
        unique_lck.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }   //  Call ~std::unique_lock
}

int main(
    int argc, char *argv[]) {

    std::thread thr1(print,"abc");
    std::thread thr2(print,"def");
    std::thread thr3(print,"xyz");


    thr1.join();
    thr2.join();
    thr3.join();


    return 0;
}