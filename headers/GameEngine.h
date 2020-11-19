#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>
#include "Map.h"

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

#endif