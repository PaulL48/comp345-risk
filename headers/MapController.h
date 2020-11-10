//
// Created by Ruslan Dallin on 2020-11-09.
//

#ifndef COMP345_RISK_COPY_MAPCONTROLLER_H
#define COMP345_RISK_COPY_MAPCONTROLLER_H

#include "GameObservers.h"

class MapContoller {
private:
    MapObserver *mapView;
    Map *mapModel;
public:
    MapContoller(MapObserver *mapView, Map *mapModel);
    void controlMap();
};

#endif // COMP345_RISK_COPY_MAPCONTROLLER_H
