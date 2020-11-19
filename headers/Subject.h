//
// Created by Ruslan Dallin on 2020-11-09.
//

#ifndef COMP345_RISK_COPY_SUBJECT_H
#define COMP345_RISK_COPY_SUBJECT_H

#include "Observer.h"
#include <list>

class Observer;

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    std::list<Observer*> *_observers;
};

#endif // COMP345_RISK_COPY_SUBJECT_H
