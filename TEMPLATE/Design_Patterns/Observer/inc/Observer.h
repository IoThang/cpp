//
// Created by tuo8hc on 10/13/25.
//

#ifndef EX01_OBSERVER_H
#define EX01_OBSERVER_H
#include "IObserver.h"
#include "Subject.h"

class Observer : public IObserver{
public:
    explicit Observer(Subject &subject);
    ~Observer() override;
    void update(std::string const& msg_from_subject) override;

    void RemoveMeFromTheList();
    void printInfo() const;
private:
    Subject &subject_;
    std::string msg_from_subject_;
    int number_;
    static int static_number_;

};


#endif //EX01_OBSERVER_H