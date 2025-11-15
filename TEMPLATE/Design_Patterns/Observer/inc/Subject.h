//
// Created by tuo8hc on 10/13/25.
//

#ifndef EX01_SUBJECT_H
#define EX01_SUBJECT_H
#include <list>

#include "ISubject.h"
#include "IObserver.h"
#include <iostream>


class Subject : public ISubject{
public:
    ~Subject() override;
    void notify() override;
    void attach(IObserver *observer) override;
    void deattach(IObserver *observer) override;

    void CreateMessage(std::string msg);
    void HowManyObservers() const;

private:
    std::list<IObserver *> list_observers_;
    std::string msg_;
};


#endif //EX01_SUBJECT_H