//
// Created by Ruslan Dallin on 2020-11-03.
//

#include "GameObservers.h"
#include "MapLoader.h"
#include "map.h"
#include <iomanip>
#include "Player.h"

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
    display();
};

bool MapObserver::victory(){
    Player *first = _subject->getContinents()->at(0).getTerritories().begin()->getOwnedBy();

    if (first == nullptr)
        return false;
    else
    {
        for (auto &cont : *_subject->getContinents())
            for (auto &terr : cont.getTerritories())
                if (first != terr.getOwnedBy())
                    return false;

        std::cout << congradulations << "\n";
        std::cout << *first << "has conquered all territories";

    }
    return true;
};

void MapObserver::display(){

    if (!victory()){
        std::cout << "-----------------------------------------------------------------------------------------------------------------------\n"
                  << std::left << std::setw(20)  << "Continents" << "Conquered Territories\n"
                  << "-----------------------------------------------------------------------------------------------------------------------\n";
        for (auto &cont: *_subject->getContinents()){
            std::cout << std::left << std::setw(20) << *cont.getName();
            for (auto &terr: cont.getTerritories()){
                if (terr.getOwnedBy() == nullptr)
                    std::cout << std::setw(15) << "[Neutral]";
                else
                    std::cout << std::setw(15) << "[" << terr.getOwnedBy()->getPlayerName() <<"]";
            }
            std::cout << "\n";
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    }


};

