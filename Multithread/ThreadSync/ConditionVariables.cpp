//
// Created by TUO8HC on 10/1/2025.
//

#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Global mutex object
std::mutex mut;
std::condition_variable condition_var;

std::string msg;
// bool flag for predicate
bool condition = false;

//  Waiting thread
void reader() {
    //  Lock mutex
    std::cout <<" Reader thread locking mutex" << std::endl;
    std::unique_lock<std::mutex> lock(mut);
    std::cout << " Reader thread has locked mutex" << std::endl;

    //  Call wait() on the condition variable
    //  Unlocks the mutex and makes this thread sleep
    std::cout << "Reader thread sleeping ..." << std::endl;
    //  Lambda predicate that checks the flag. To avoid lost or spurious wakeup
    condition_var.wait(lock, [] {return condition;});
    //  The condition variable wake this thread up and locks the mutex
    std::cout << " Reader thread wakeup" << std::endl;
    std::cout << "Message: " << msg << std::endl;
}

//  Notifying thread
void writer() {
    std::cout <<" Writer thread locking mutex" << std::endl;
    {
        std::cout << " Writer thread has locked mutex" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //  Lock the mutex
        std::lock_guard<std::mutex> lock(mut);
        //  Modify the shared data
        std::cout << " Writer modifying data..." << std::endl;
        msg = "Pass interview :)";
        // Set the flag
        condition = true;
        std::cout << "Writer thread unlock mutex" << std::endl;
    }   //  Release lock

    //  Notify the condition variable
    std::cout << "Writer thread sends notification ..." << std::endl;\
    //  Wake up 1 thread is waiting on the conditon variable by the notification
    // condition_var.notify_one();
    //  Wake up all thread is waiting on the conditon variable by the notification
    condition_var.notify_all();
}

int main(
    int argc, char *argv[]) {

    std::thread thr1(reader);
    std::thread thr2(writer);

    std::thread thr3(reader);
    std::thread thr4(reader);

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();

    return 0;
}