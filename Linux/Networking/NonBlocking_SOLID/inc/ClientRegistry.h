//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_CLIENTREGISTRY_H
#define EX01_CLIENTREGISTRY_H
#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "ClientInfo.h"
#include "ISubject.h"

namespace networking {
    class ClientRegistry : public ISubject {
    public:

        void attach(std::shared_ptr<ClientInfo> observers, std::string room) override;
        void detach(std::shared_ptr<ClientInfo> observers, std::string room) override;
        void notify(std::shared_ptr<ClientInfo> observers, std::string room) override;

        std::unique_ptr<ClientInfo> get_client_by_fd(int fd);
    private:
        std::unordered_map<int, std::unique_ptr<ISubject>> fd_to_info_;
        std::unordered_map<std::string, int> name_to_fd_;
        std::unordered_map<std::string, std::shared_ptr<IObserver>> room_observers_;
        std::shared_mutex registry_mutex_;
    };
}



#endif //EX01_CLIENTREGISTRY_H