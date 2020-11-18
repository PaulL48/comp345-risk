#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>
#include "Map.h"

static int totalPlayers; 
static std::size_t selectedMap;
static int phaseObserver;
static int statObserver; 
static std::vector<std::string> mapNames; 

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