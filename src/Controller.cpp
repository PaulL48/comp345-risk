//
// Created by Ruslan Dallin on 2020-11-09.
//

#include "Controller.h"
#include <MapLoader.h>


MapController::MapController(MapObserver* newView, Map* newModel) {
    mapView = newView;
    mapModel = newModel;
}

PhaseController::PhaseController(PhaseObserver* newView, GameENgine* newModel) {
    phaseView = newView;
    phaseModel = newModel;
}

