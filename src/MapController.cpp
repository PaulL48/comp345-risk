//
// Created by Ruslan Dallin on 2020-11-09.
//

#include "MapController.h"
#include <MapLoader.h>

// THIS IS A TEST FILE IT SHOULD BE DELETED BEFORE SUBMISSION //

MapContoller::MapContoller(MapObserver* newView, Map* newModel) {
    mapView = newView;
    mapModel = newModel;
}

void MapContoller::controlMap() {
    while (true)
    {
        int command;
        std::cout << "Select option and type enter)\n";
        std::cin >> command;

        switch (command)
        {
        case 1:
            mapModel->testNotify();
            break;
        case 2:
            return;
        case 3:
            //std::cout << *mapModel->getContinents()->at(0).getName();
            break;
        }
    }
}

int main()
{
    Map *model = new Map (MapLoader::createMap("../maps/europe.map")); // This should prob be in the main game loop.
    MapObserver *view = new MapObserver(model);
    MapContoller *contoller = new MapContoller(view, model);
    contoller->controlMap();

    delete view;
    delete model;
    delete contoller;

    return 0;
}
