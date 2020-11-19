#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Player.h"

extern int totalPlayers; 
extern std::size_t selectedMap;
extern int phaseObserver;
extern int statObserver; 
extern std::vector<std::string> mapNames; 

class GameEngine
{
public: 
    GameEngine();
    ~GameEngine(); 
}; 


class MapSelect
{
public: 
    MapSelect(); 
    ~MapSelect(); 
    
}; 

class PlayerAmount
{
public:
    PlayerAmount();
    ~PlayerAmount(); 
    int getPlayers();
    void setPlayers(int totalPlayers); 
};

class ControlObservers
{
public: 
    ControlObservers();
    ~ControlObservers();

}; 

class GameStartup{
    private:
        int* numPlayers;
        std::vector<Player>* players;
        Map* map;
        std::vector<int>* orderPlayers;
        int getNumberOfArmies();
        std::vector<Player>& intializePlayers(const int numArmies);
        std::vector<int>& intitializeOrderPlayers(const int numPlayers);
        
        

    public:
        GameStartup(const int numPlayer, const Map& map);                          // Constructor
        GameStartup();
        ~GameStartup();              
        void startupPhase();
        std::vector<Player>& getPlayers();
        Map& getMap();
        std::vector<int>& getOrderPlayers();
};
#endif