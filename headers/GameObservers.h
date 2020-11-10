//
// Created by Ruslan Dallin on 2020-11-03.
//

#ifndef COMP345_RISK_GAMEOBSERVERS_H
#define COMP345_RISK_GAMEOBSERVERS_H

#include "Observer.h"
#include "Map.h"

class MapObserver : public Observer {
public:
    MapObserver(Map* s);
    ~MapObserver();
    void Update();
    void display();
private:
    Map *_subject;
};


#endif //COMP345_RISK_GAMEOBSERVERS_H
