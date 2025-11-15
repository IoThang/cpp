//
// Created by TUO8HC on 10/3/2025.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class DownloadManager {
public:
    DownloadManager(int total, int chunk)
        : total_size(total), chunk_size(chunk),
          downloaded(0), finished(false) {}

    void run() {
        std::thread t1(&DownloadManager::fetcher, this);
        std::thread t2(&DownloadManager::progress_bar, this);
        std::thread t3(&DownloadManager::processor, this);

        t1.join();
        t2.join();
        t3.join();
    }

private:
    int total_size;
    int chunk_size;
    int downloaded;
    bool finished;

    std::mutex mtx;
    std::condition_variable cv;

    // Thread 1: download data
    void fetcher() {
        while (downloaded < total_size) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            std::unique_lock<std::mutex> lock(mtx);
            downloaded += chunk_size;
            if (downloaded > total_size) downloaded = total_size;

            cv.notify_all();
        }

        {
            std::unique_lock<std::mutex> lock(mtx);
            finished = true;
        }
        cv.notify_all();
    }

    // Thread 2: show progress bar
    void progress_bar() {
        int last_downloaded = -1;
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return downloaded != last_downloaded || finished; });

            if (downloaded != last_downloaded) {
                last_downloaded = downloaded;
                int percent = (downloaded * 100) / total_size;
                std::cout << "[Progress] Downloaded: " << percent << "%\n";
            }

            if (finished) break;
        }
    }

    // Thread 3: process after finished
    void processor() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return finished; });

        std::cout << "[Processor] Download complete. Now processing data...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[Processor] Data processed successfully!\n";
    }
};

int main() {
    DownloadManager manager(100, 10);  // 100MB, fetch 10MB per step
    manager.run();
    return 0;
}
