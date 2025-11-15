//
// Created by tuo8hc on 11/6/25.
//

#include "../../../inc/ClientRegistry.h"

#include "ClientInfoFactory.h"

//  This function won't call directly, It will be called by another function => Don't lock thread here
void networking::ClientRegistry::attach(std::shared_ptr<IObserver> obs, std::string room_id) {
    room_observers_[room_id].push_back(obs);
}

void networking::ClientRegistry::detach(std::shared_ptr<IObserver> obs, std::string room_id) {
    auto& observers = room_observers_[room_id];
    if (!observers.size())
        // observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    //  Clean up room if there is no observers in the room
    if (observers.empty()) {
        room_observers_[room_id].clear();
        room_observers_.erase(room_id);
    }
}

void networking::ClientRegistry::notify(const RoomEvent& event, const std::string& source_name, const std::string& room_id) {
    auto it = room_observers_.find(room_id);
    if (it != room_observers_.end()) {
        for (auto& observer : it->second) {
            observer->update(event, source_name, room_id);
        }
    }
}

void networking::ClientRegistry::insert(int fd, std::unique_ptr<ClientInfo> info) {
    std::unique_lock<std::shared_mutex> wlock(registry_mutex_);
    fd_to_info_[fd] = std::move(info);
    fd_to_name_[fd] = "";   //  Init first and add data later
    attach(std::shared_ptr<ClientInfo> (fd_to_info_[fd].get()), "general");
}

void networking::ClientRegistry::erase(int fd) {
    std::unique_lock<std::shared_mutex> wlock(registry_mutex_);
    auto info_it = fd_to_info_.find(fd);
    if (info_it != fd_to_info_.end()) {
        std::string name = info_it->second->getName();
        std::string room_id = info_it->second->getRoomID();
        detach(std::shared_ptr<ClientInfo>(info_it->second.get()), room_id);
        fd_to_info_.erase(info_it);
    }
}

networking::ClientInfo* networking::ClientRegistry::get_client_by_fd(int fd) {
    std::shared_lock<std::shared_mutex> rlock(registry_mutex_);
    auto it = fd_to_info_.find(fd);
    return (it != fd_to_info_.end()) ? it->second.get() : nullptr;
}

void networking::ClientRegistry::set_name_by_fd(const std::string& name, int fd) {
    fd_to_name_[fd] = name;
}

std::string networking::ClientRegistry::get_name_by_fd(int const fd) const {
    return fd_to_name_.at(fd);
}

bool networking::ClientRegistry::isNameRegistered(std::string name) const {
    for (auto& it : fd_to_name_) {
        if (it.second == name) {
            return true;
        }
    }
    return false;
}

int networking::ClientRegistry::get_fd_by_name(const std::string& name) const {
    for (auto& it : fd_to_name_) {
        if (it.second == name) {
            return it.first;
        }
    }
    return -1;
}

void networking::ClientRegistry::changeRoom(int fd, const std::string& new_room) {
    std::unique_lock<std::shared_mutex> wlock(registry_mutex_);
    wlock.unlock();
    ClientInfo* info = get_client_by_fd(fd);
    std::unique_lock<std::shared_mutex> wlock_2(registry_mutex_);
    if (info) {
        // std::string old_room = info->room_id_;
        // detach(std::shared_ptr<ClientInfo>(info), old_room);
        // ClientInfoFactory::updateRoom(*info, new_room);
        // attach(std::shared_ptr<ClientInfo>(info), new_room);
        // Notify old/new room
        // notify(RoomEvent::LEAVE, info->name_, old_room);
        // notify(RoomEvent::JOIN, info->name_, new_room);
    }
}