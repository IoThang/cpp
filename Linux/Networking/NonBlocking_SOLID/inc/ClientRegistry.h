//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_CLIENTREGISTRY_H
#define EX01_CLIENTREGISTRY_H
#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "ClientInfo.h"
#include "ISubject.h"

namespace networking {
    class ClientRegistry : public ISubject {
    public:
        // ~ClientRegistry() override = default;

        //  Observer method
        void attach(std::shared_ptr<IObserver> obs, std::string room_id) override;
        void detach(std::shared_ptr<IObserver> obs, std::string room_id) override;
        void notify(const RoomEvent& event, const std::string& source_name, const std::string& room_id) override;

        //  Helper method
        void insert(int fd, std::unique_ptr<ClientInfo> info);
        void erase(int fd);
        ClientInfo* get_client_by_fd(int fd);
        void set_name_by_fd(const std::string& name, int fd);
        std::string get_name_by_fd(int fd) const;
        int get_fd_by_name(const std::string& name) const;
        bool isNameRegistered(std::string name) const;
        void changeRoom(int fd, const std::string& new_room);

    private:
        std::unordered_map<int, std::unique_ptr<ClientInfo>> fd_to_info_;
        std::unordered_map<int, std::string> fd_to_name_;
        std::unordered_map<std::string, std::vector<std::shared_ptr<IObserver>> > room_observers_;
        std::shared_mutex mutable registry_mutex_;
    };
}



#endif //EX01_CLIENTREGISTRY_H