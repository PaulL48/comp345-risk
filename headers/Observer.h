//
// Created by Ruslan Dallin on 2020-11-09.
//

#ifndef COMP345_RISK_COPY_OBSERVER_H
#define COMP345_RISK_COPY_OBSERVER_H

class Observer {
public:
    ~Observer();
    virtual void Update() = 0;
protected:
    Observer();
};


#endif // COMP345_RISK_COPY_OBSERVER_H
