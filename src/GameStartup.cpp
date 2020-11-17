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
    *this->orderPlayers = intitializeOrderPlayers(numPlayers);
    return;
}
std::vector<int>& GameStartup::intitializeOrderPlayers(const int numPlayers){
     std::vector<int>* orderPlayers = new std::vector<int>(numPlayers,10);
     std::vector<int> numTerritoriesOwned = std::vector<int>(numPlayers,0);
     for(int i = 0; i < numTerritoriesOwned.size(); i++){
         numTerritoriesOwned.push_back(i);
     }
     int index= 0;
     for(int i = 0 ; i < orderPlayers->size();i ++){
         index = (rand() % numTerritoriesOwned.size());
         int val = numTerritoriesOwned.at(index);
         orderPlayers->at(i) = val;
     }
     return *orderPlayers;
}


std::vector<Player>& GameStartup::intializePlayers(const int numArmies){
    Graph<Territory> territories = map->getGraph();
    std::vector<Player>* playerList  = new std::vector<Player>(numPlayers);
    std::vector<int> numTerritoriesOwned = std::vector<int>(numPlayers,0);
    int territoriesLeft = territories.size();
    int territoriesPerPlayer = territoriesLeft/numPlayers;
    for (int i = 0; i < numPlayers; i++){
        std::string *playerName = new std::string("Player " + std::to_string(i + 1));
        Hand hand;
        OrdersList orderlist;
        std::vector<Territory>* toAttack = new std::vector<Territory>();
        std::vector<Territory>* toDefend = new std::vector<Territory>();
        Player p = Player(*playerName,*toAttack,*toDefend, hand, orderlist,numArmies);
        playerList->push_back(p);
    }
    std::vector<int> numTerritoriesOwned = std::vector<int>(numPlayers);
    int index= 0;
    for(Territory territory: territories ){
        bool validInsert = true;
        
        while(validInsert){
            index = (rand() % numPlayers);
            if(territoriesLeft == 1 && territories.size() % numPlayers != 0 ){
                territory.setPlayer(playerList->at(index));
                validInsert= false;
                territoriesLeft--;
            }else{
                if(numTerritoriesOwned.at(index) != territoriesPerPlayer){
                    int val = numTerritoriesOwned.at(index) + 1;
                    territory.setPlayer(playerList->at(index));
                    numTerritoriesOwned.at(index) = val;
                    territoriesLeft--;
                    validInsert=false;
                }
            }
        }
    }
    for (int i = 0; i < numPlayers; i++){
        Player player = playerList->at(i);
        std::vector<Territory> ownedTerritories = map->getPlayersTerritories(player);
        for(Territory territory: ownedTerritories){
            std::unordered_set<Territory> neighborTerritories = *map->getNeighbors(territory);
            for(Territory neighborTerritory : neighborTerritories){
                if( !(neighborTerritory.getOwningPlayer() == player)){
                    player.toDefend().push_back(territory);
                    if(!(std::find(player.toAttack().begin(), player.toAttack().end(), neighborTerritory) != player.toAttack().end())) {
                         player.toAttack().push_back(neighborTerritory);
                    }
                }
            }
        }
        playerList->at(i) = player;
    }

    return *playerList;
 }