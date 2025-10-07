//
// Created by TUO8HC on 10/5/2025.
//
#ifndef __TIMER_H__
#define __TIMER_H__
#pragma once

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

#endif