//
// Created by TUO8HC on 10/1/2025.
//

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex shmut;

int shareddata = 0;

// The read thread uses a shared lock
void read(int const& idx) {
    std::shared_lock shared_lck(shmut);
    //  Start of CS
    std::cout << "Thread reader id: " << idx << ": "<< shareddata << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // End of CS

}
// The write thread uses an exclusive lock
void write(int const& idx) {
    std::lock_guard lck_guard(shmut);
    // Start of CS
    shareddata++;
    std::cout << "Thread writer id: " << idx << ": "<< shareddata << std::endl;
    // End of CS
}   //  ~std::lock_guard() -> unlock

int main(
    int argc, char *argv[]) {

    std::vector<std::thread> thr;
    thr.reserve(20);

    for (int i = 0; i < 20; i++) {
        thr.push_back(std::thread(read, i));
    }

    for (int i = 0; i < 2; i++) {
        thr.push_back(std::thread(write, i));
    }
    
    for (int i = 20; i < 40; i++) {
        thr.push_back(std::thread(read, i));
    }

    for (auto& it : thr)
        it.join();

    return 0;
}