//
// Created by tuo8hc on 10/29/25.
//

#ifndef EX01_TASK_H
#define EX01_TASK_H
#include <string>
#include <variant>
#include <vector>

namespace networking {
    enum class TaskType {
        ProcessRecv = 0,
        Broadcast,
        SendSpecific,
        Cleanup
    };
    //  Move-only
    struct Task {
    // public:
        Task() = default;
        Task(TaskType type, int fd) : type_(type), fd_(fd) {}
        Task(TaskType type, int fd, std::string msg) : type_(type), fd_(fd), data_(std::move(msg)) {}
        Task(TaskType type, int fd, std::vector<char> buffer) : type_(type), fd_(fd), data_(std::move(buffer)) {}

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;
        Task(Task&&) noexcept = default;
        Task& operator=(Task&&) noexcept = default;

        TaskType type_;
        int fd_{};
        std::variant<std::monostate, std::string, std::vector<char>> data_;
    };
}

#endif //EX01_TASK_H