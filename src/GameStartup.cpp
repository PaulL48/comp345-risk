#include "Player.h"
#include "Map.h"
#include "GameStartup.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



GameStartup::GameStartup(const int numPlayer, const Map& map) :
    numPlayers(numPlayer),
    map( new Map(map))
{
}
GameStartup::GameStartup() :
    numPlayers(0),
    map( new Map)
{
}


std::vector<Player> &GameStartup::getPlayers(){
    return *players;
}

int GameStartup::getNumberOfArmies(int numPlayer){
    switch(numPlayers){
        case 2:
          return 40;
        case 3:
            return 35;
        case 4:
            return 30;
        case 5:
            return 25;
        default:
            return 0;
    }
}


void GameStartup::startupPhase(){
    int numArmies = getNumberOfArmies(numPlayers);
    *this->players = intializePlayers(numArmies);
    return;
}



 std::vector<Player>& GameStartup::intializePlayers(int numArmies){
    std::vector<Player>* playerList  = new std::vector<Player>(numPlayers);
    std::vector<Territory>* territoriesLeft = new std::vector<Territory>();
    for (int i = 0; i < numPlayers; i++){
        std::string *playerName = new std::string("Player " + std::to_string(i + 1));
        Hand hand;
        OrdersList orderlist;
        std::vector<Territory>* toAttack = new std::vector<Territory>();
        std::vector<Territory>* toDefend = new std::vector<Territory>();
        int index = (rand() % territoriesLeft->size());
        Territory toDef = territoriesLeft->at(index);
        toDefend->push_back(toDef);
        toAttack->erase(std::remove(toAttack->begin(), toAttack->end(), toDef), toAttack->end());
        Player p = Player(*playerName,*toAttack,*toDefend, hand, orderlist,numArmies);
        playerList->push_back(p);
    }
    return *playerList;
 }