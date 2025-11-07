//
// Created by tuo8hc on 11/6/25.
//

#ifndef EX01_CLIENTINFO_H
#define EX01_CLIENTINFO_H
#include <chrono>
#include <set>
#include <string>

namespace networking {
    class ClientInfo : public IObserver {
    public:
        explicit ClientInfo(int fd);
        ~ClientInfo();

        ClientInfo(const ClientInfo&) = delete;
        ClientInfo& operator=(const ClientInfo&) = delete;

        void update() override;
        void setName(std::string name);
        std::string getName() const;

    private:
        std::string name_;
        int fd_;
        std::string room_id_;
        std::chrono::time_point<> join_time_;
        std::chrono::time_point<> last_active_;
        size_t msg_count_;
        std::set<std::string> friends_list_;
    };
}



#endif //EX01_CLIENTINFO_H