//
// Created by tuo8hc on 10/22/25.
//

#include "../inc/ClientHandler.h"

#include <cstring>
#include <iostream>
#include <sys/epoll.h>

networking::ClientHandler::ClientHandler(ThreadPool& pool, ClientRegistry& registry) : pool_(pool), registry_(registry) {}

// Client handler: Handles incoming messages and echoes (can be extended for broadcast receive)
void networking::ClientHandler::handle(int fd, event_t events) {
    if (!(events & EPOLLIN)) return;
    //  =========================== READING PROCESS =================================
    std::string nameClient = registry_.get_name_by_fd(fd);
    char buffer[1024];
    ssize_t bytes_read = NetworkUtility::read(fd,buffer,sizeof(buffer) - 1);
    //  Handle for disconnect and fail state from read
    if(bytes_read <= 0) {
        if (bytes_read == 0) {
            // Check for "exit" command from client
            if (strcmp(buffer, "exit\n") != 0) {
                std::cout << "[Server] Client fd=" << fd << " requested exit. Disconnecting." << std::endl;
            } else {
                if (nameClient.empty()) {
                    std::cout << "[Client fd = " << fd << "] Disconnected" << std::endl;
                }
                else {
                    std::cout << "[" << nameClient << "] Disconnected" << std::endl;
                }

            }
        }
        else {
            std::cerr << "[ERROR] : NetworkUtility::read failed on fd = " << fd << " : " << strerror(errno) << std::endl;
        }
        // Signal disconnect via virtual or callback; here, just close
        NetworkUtility::close(fd);
        return;
    }
    buffer[bytes_read] = '\0';
    if (nameClient.empty()) {
        std::cout << "[Client fd = " << fd << "] Received: " << buffer << std::endl;
    }
    else {
        std::cout << "[" << nameClient << "] Received: " << buffer << std::endl;
    }


    //===================================================================================
    //  TODO: Will refactor later to avoid static array and make it functional
    char taskName[50] = "";
    char taskData[50] = "";
    char *start = strchr(buffer, '[');
    char *end   = strchr(buffer, ']');
    char *colon = strchr(buffer, ':');

    if (start && end && colon) {
        size_t len_name = end - start - 1;
        strncpy(taskName, start + 1, len_name);
        taskName[len_name] = '\0';
        strcpy(taskData, colon + 1);
    }
    if (taskName && taskData) {
        if (!strcmp(taskName, "SETNAME")) {
            std::string tempName = taskData;
            //  TODO: Dummy data to write :)
            std::string tempName2 = taskData;
            // pool_.enqueue({TaskType::SetName, fd, std::move(tempName)});
            ClientInfo* info = registry_.get_client_by_fd(fd);
            registry_.set_name_by_fd(tempName, fd);
            info->name_ = std::move(tempName);
            return;
        }
        else if (!strcmp(taskName, "JOINROOM")) {
            std::string tempRoom = taskData;
            //  TODO: Dummy data to write :)
            std::string tempRoom2 = taskData;
            // pool_.enqueue({TaskType::JoinRoom, fd, std::move(tempRoom)});
            ClientInfo* info = registry_.get_client_by_fd(fd);
            info->room_id_ = std::move(tempRoom);
            return;
        }
    }

    std::string buff = buffer;
    std::vector<int> listOfNames = parseMsgAndLookUp(buff);
    for (auto const& it : listOfNames) {
        buff = "[" + registry_.get_name_by_fd(fd) + "] " + buff;
        NetworkUtility::write(it,buff.data(),buff.size());
    }

    //  Echo back
    // NetworkUtility::write(fd,buffer,static_cast<size_t>(bytes_read));
}


std::vector<int> networking::ClientHandler::parseMsgAndLookUp(std::string& line) {
    std::vector<int> listOfNames;
    size_t pos_colon = line.find(":", 0);
    std::string names = line.substr(0, pos_colon);
    while (names.find(",") != std::string::npos) {
        size_t pos_comma = names.find(",");
        //  Get the single name
        std::string name = names.substr(0, pos_comma - 1);
        //  Lookup the finding name in registry data
        int valid_fd = registry_.get_fd_by_name(name);
        if (valid_fd > 2 /*0,1,2 is stdin,out,err, skip this three numbers*/) {
            listOfNames.push_back(valid_fd);
        } else {
            std::cout << "Client with name: " << name << "not register yet" << std::endl;
        }
        //  Update names to continue loop for finding
        names = names.substr(pos_comma + 1);
    }
    int remain_fd = registry_.get_fd_by_name(names);
    if (remain_fd > 2 /*0,1,2 is stdin,out,err, skip this three numbers*/) {
        listOfNames.push_back(remain_fd);
    }
    else {
        std::cout << "Client with name: " << names << "not register yet" << std::endl;
    }
    //  Truncate buffer to get the message
    line = line.substr(pos_colon + 1);
    return listOfNames;
}