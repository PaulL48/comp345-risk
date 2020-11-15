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
        int getNumberOfArmies(int numPlayer);
        std::vector<Player>& intializePlayers(int numArmies);
        
        

    public:
        GameStartup(const int numPlayer, const Map& map);                          // Constructor
        GameStartup();
        ~GameStartup();              
        void startupPhase();
        std::vector<Player>& getPlayers();
};
#endif