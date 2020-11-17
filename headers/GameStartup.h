#ifndef GAMESTART_H
#define GAMESTART_H
#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Player.h"



class GameStartup{
    private:
        int numPlayers;
        std::vector<Player>* players;
        Map* map;
        std::vector<int>* orderPlayers;
        int getNumberOfArmies(int numPlayer);
        std::vector<Player>& intializePlayers(const int numArmies);
        std::vector<int>& intitializeOrderPlayers(const int numPlayers);
        
        

    public:
        GameStartup(const int numPlayer, const Map& map);                          // Constructor
        GameStartup();
        ~GameStartup();              
        void startupPhase();
        std::vector<Player>& getPlayers();
        std::vector<int>& getOrderPlayers();
};
#endif