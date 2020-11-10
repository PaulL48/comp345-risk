//
// Created by Ruslan Dallin on 2020-11-03.
//

#include "GameObservers.h"
#include "map.h"
#include "MapLoader.h"

MapObserver::MapObserver(Map* s){
    //Upon instantiation, attaches itself to a ClockTimer
    _subject = s;
    _subject->Attach(this);
};

MapObserver::~MapObserver(){
    //Upon destruction, detaches itself from its ClockTimer��
    _subject->Detach(this);
};

void MapObserver::Update(){
    std::cout << "inside update";
    display();
};
void MapObserver::display(){

    std::cout << "inside display";
};


//int main()
//{
//    Map map = MapLoader::loadMap("../maps/trivia.map");
//    std::cout << map;
//    return 0;
//}
