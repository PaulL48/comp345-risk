//
// Created by Ruslan Dallin on 2020-11-09.
//

#ifndef COMP345_RISK_CONTROLLER_H
#define COMP345_RISK_CONTROLLER_H

#include "GameObservers.h"
#include "GameEngine.h"


class MapController {
private:
    MapObserver *mapView;
    Map *mapModel;
public:
    MapController(MapObserver *mapView, Map *mapModel);
};

class PhaseController {
private:
    PhaseObserver *phaseView;
    GameEngine *phaseModel;
public:
    MapController(PhaseObserver *phaseView, GameEngine *phaseModel);
};

#endif // COMP345_RISK_COPY_MAPCONTROLLER_H
