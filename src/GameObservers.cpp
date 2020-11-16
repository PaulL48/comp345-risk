//
// Created by Ruslan Dallin on 2020-11-03.
//

#include "GameObservers.h"
#include "MapLoader.h"
#include "Player.h"
#include "map.h"
#include <iomanip>
#include <set>
#include "GameEngine.h"

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
    displayMap();
    displayPlayers();
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

        std::cout << congratulations << "\n";
        std::cout << *first << "has conquered all territories";

    }
    return true;
};

std::set<std::string> MapObserver::getPlayerList (){
    std::set<std::string> playerSet;

    for (auto &cont: *_subject->getContinents()){
        for (auto &terr: cont.getTerritories()){
            if (terr.getOwnedBy() != nullptr)
                playerSet.insert(terr.getOwnedBy()->getPlayerName());
        }
    }
    return playerSet;
}

void MapObserver::displayMap(){

    if (!victory()){
        std::cout << "-----------------------------------------------------------------------------------------------------------------------\n"
                  << std::left << std::setw(20)  << "Continents" << "Territory Ownership\n"
                  << "-----------------------------------------------------------------------------------------------------------------------\n";
        for (auto &cont: *_subject->getContinents()){
            std::cout << std::left << std::setw(20) << *cont.getName() + ":";
            for (auto &terr: cont.getTerritories()){
                if (terr.getOwnedBy() == nullptr)
                    std::cout << std::setw(15) << "[Neutral]";
                else
                    std::cout << std::setw(15) << "[" << terr.getOwnedBy()->getPlayerName() <<"]";
            }
            std::cout << "\n";
        }
    }
};

void MapObserver::displayPlayers(){
    std::set<std::string> playerSet = getPlayerList();
    double ownedCount;
    double count;

    if (!victory()){
        std::cout << "-----------------------------------------------------------------------------------------------------------------------\n"
                  << std::left << std::setw(20)  << "Players" << "Percentage of world conquered\n"
                  << "-----------------------------------------------------------------------------------------------------------------------\n";
        for (auto &player: playerSet){
            std::cout << std::left << std::setw(20) << player + ":" << "[";
            ownedCount = 0;
            count = 0;
            for (auto &cont: *_subject->getContinents()){
                for (auto &terr: cont.getTerritories()){
                    if (terr.getOwnedBy()->getPlayerName() == player){
                        std::cout << std::setw(1) << "+";
                        ownedCount++;
                    }
                    else
                        std::cout << std::setw(1) << "-";
                    count++;
                }
            }
            std::cout << std::setw(15) << std::fixed << std::setprecision(3) << ownedCount/count << '%';
            std::cout << "\n";
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    }
};


PhaseObserver::PhaseObserver(GameEngine* s){
    //Upon instantiation, attaches itself to a ClockTimer
    _subject = s;
    _subject->Attach(this);
};

PhaseObserver::~PhaseObserver(){
    //Upon destruction, detaches itself from its ClockTimer��
    _subject->Detach(this);
};

void PhaseObserver::Update(){
    displayPhase();
};

void PhaseObserver::displayPhase(){

}

