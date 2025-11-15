//
// Created by tuo8hc on 10/29/25.
//

#include "../inc/DefaultTaskProcessor.h"



networking::DefaultTaskProcessor::DefaultTaskProcessor(ClientRegistry& registry) : registry_(registry) {}

void networking::DefaultTaskProcessor::process(const Task& task) {
    // Read lock for most ops (e.g: rlock: CLeanUp,)
    switch (task.type_) {
        case TaskType::ProcessRecv: {
            //  Leave here. No feature is implemented
            break;
        }
        case TaskType::Broadcast: {
            //  This task should be removed, since in handler will work effective than here
            break;
        }
        case TaskType::SendSpecific: {
            //  This task should be removed, since in handler will work effective than here
            break;
        }
        case TaskType::Cleanup: {
            //  Worker side: close everything related to worker
            //  Deadlock here if rlock doesn't release lock
            // std::unique_lock<std::shared_mutex> wlock(clients_mutex);
            // auto it = clients_.find(task.fd_);
            // if (it != clients_.end()) {
            //     clients_.erase(it);
            // }
            //  Shouldn't close fd here. Violating the purpose of worker (Reactor will handler IO)
            std::cout << "[Worker Id=] Cleaned up fd=" << task.fd_ << std::endl;
            break;
        }
        case TaskType::RegisterClient: {
            std::unique_lock<std::shared_mutex> wlock(clients_mutex);
            auto info = ClientInfoFactory::create(task.fd_);
            registry_.insert(task.fd_ ,std::move(info));
            std::cout << "[Worker] Registered " << task.fd_ << std::endl;
            break;
        }
        case TaskType::SetName: {
            std::unique_lock<std::shared_mutex> wlock(clients_mutex);
            ClientInfo* clientInfo = registry_.get_client_by_fd(task.fd_);
            clientInfo->name_ = std::get<std::string>(task.data_);
            std::cout << "[Worker Id=] Set fd=" << task.fd_  <<" with the name: " <<  clientInfo->name_ << std::endl;
            break;
        }
        case TaskType::JoinRoom: {
            std::unique_lock<std::shared_mutex> wlock(clients_mutex);
            auto room_id= std::get<std::string>(task.data_);
            if (!room_id.empty()) {
                registry_.changeRoom(task.fd_, room_id);
            }
            break;
        }
        default: {
            std::cerr << "[Worker Id=] Unknown task type" << std::endl;
        }
    }
}
