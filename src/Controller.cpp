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

//                      TO BE DELECTED!
//int main()
//{
//    Map *model = new Map (MapLoader::createMap("../maps/europe.map")); // This should prob be in the main game loop.
//    MapObserver *view = new MapObserver(model);
//    MapController *contoller = new MapController(view, model);
//
//    delete view;
//    delete model;
//    delete contoller;
//
//    return 0;
//}
