//
// Created by TUO8HC on 9/30/2025.
//

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

const std::vector<std::string> joiner{"Thang", "Tan", "Nam", "Hoa", "Long"};


void play(int idx) {

}

int main(
    int argc, char *argv[]) {

    std::vector<std::thread> thr;
    thr.reserve(joiner.size());

    for (int i = 0; i < joiner.size(); i++) {
        thr.push_back(std::move(std::thread(play, i)));
    }

    for (auto& it: thr) {
        it.join();
    }
    return 0;
}
