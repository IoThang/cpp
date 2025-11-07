//
// Created by tuo8hc on 10/29/25.
//

#include "../inc/DefaultTaskProcessor.h"



networking::DefaultTaskProcessor::DefaultTaskProcessor(std::unordered_map<int, std::string> &client_map, ClientRegistry& registry)
        : clients_(client_map), registry_(registry) {}

void networking::DefaultTaskProcessor::process(const Task& task) {
    // Read lock for most ops (e.g: rlock: CLeanUp,)
    std::shared_lock rlock(clients_mutex);
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
            rlock.unlock();
            std::unique_lock<std::shared_mutex> wlock(clients_mutex);
            auto it = clients_.find(task.fd_);
            if (it != clients_.end()) {
                clients_.erase(it);
            }
            //  Shouldn't close fd here. Violating the purpose of worker (Reactor will handler IO)
            std::cout << "[Worker Id=] Cleaned up fd=" << task.fd_ << std::endl;
            break;
        }
        case TaskType::RegisterClient: {

        }
        case TaskType::SetName: {
            std::unique_ptr<ClientInfo> clientInfo = registry_.get_client_by_fd(task.fd_);
            clientInfo->setName(std::get<std::string>(task.data_));
            std::cout << "[Worker Id=] Set fd=" << task.fd_  <<" with the name: " << clientInfo->getName() << std::endl;
            break;
        }
        case TaskType::JoinRoom: {

        }
        default: {
            std::cerr << "[Worker Id=] Unknown task type" << std::endl;
        }
    }
}
