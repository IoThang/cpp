#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

constexpr int TOTAL_SIZE = 100;   // MB
constexpr int CHUNK_SIZE = 10;    // MB mỗi lần tải
int downloaded = 0;               // dữ liệu đã tải

std::mutex mtx;
std::condition_variable cv;
bool finished = false;            // báo hiệu đã tải xong

// Thread 1: fetcher (giả lập tải dữ liệu qua network)
void fetcher() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // giả lập độ trễ mạng
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (downloaded >= TOTAL_SIZE) {
                finished = true;
                cv.notify_all();
                break;
            }
            downloaded += CHUNK_SIZE;
            if (downloaded > TOTAL_SIZE) downloaded = TOTAL_SIZE;
        }
        cv.notify_all(); // báo cho progress/processor biết có dữ liệu mới
    }
}

// Thread 2: progress bar
void progress_bar() {
    int last_downloaded = -1;  // giá trị trước đó
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return downloaded != last_downloaded || finished; });

        if (downloaded != last_downloaded) {
            last_downloaded = downloaded;
            int percent = (downloaded * 100) / TOTAL_SIZE;
            std::cout << "[Progress] Downloaded: " << percent << "%\n";
        }

        if (finished) break;
    }
}


// Thread 3: processor
void processor() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return finished; });  // chờ tới khi tải xong
    std::cout << "[Processor] Download complete. Processing data...\n";
    lock.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(2)); // giả lập xử lý
    std::cout << "[Processor] Processing finished.\n";
}

int main() {
    std::thread t1(fetcher);
    std::thread t2(progress_bar);
    std::thread t3(processor);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
