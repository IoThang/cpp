//
// Created by tuo8hc on 10/13/25.
//

#include "../inc/Observer.h"

Observer::Observer(Subject &subject) : subject_(subject) {
    this->subject_.attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
    this->number_ = static_number_;
}

Observer::~Observer() {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
}

void Observer::update(std::string const& msg_from_subject) {
    msg_from_subject_ = msg_from_subject;
    printInfo();
}

void Observer::RemoveMeFromTheList() {
    subject_.deattach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
}

void Observer::printInfo() const {
    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->msg_from_subject_ << "\n";
}