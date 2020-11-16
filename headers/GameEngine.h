#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>
#include "Map.h"

int totalPlayers; 

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
    std::vector<Map *> *maps;
    std::vector<std::string> mapNames; 
}; 

class PlayerAmount
{
public:
    PlayerAmount();
    ~PlayerAmount(); 
    int getPlayers();
    void setPlayers(int totalPlayers); 
};

#endif