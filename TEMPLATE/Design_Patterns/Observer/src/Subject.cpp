//
// Created by tuo8hc on 10/13/25.
//

#include "../inc/Subject.h"

Subject::~Subject() {
    std::cout << "Goodbye, I was the Subject.\n";
}


void Subject::notify() {
    std::list<IObserver *>::iterator iter = list_observers_.begin();
    HowManyObservers();
    while (iter != list_observers_.end()) {
        (*iter)->update(msg_);
        ++iter;
    }
}

void Subject::attach(IObserver *observer) {
    list_observers_.emplace_back(observer);
}

void Subject::deattach(IObserver *observer) {
    list_observers_.remove(observer);
}

void Subject::CreateMessage(std::string msg = "Empty") {
    this->msg_ = msg;
    notify();
}

void Subject::HowManyObservers() const {
   std::cout << "There are " << list_observers_.size() << " observers in the list" << std::endl;
}