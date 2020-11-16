#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"


GameEngine::GameEngine()
{
}

GameEngine::~GameEngine(){}

MapSelect::MapSelect()
{
    int totalMaps = mapNames.size(); 
    int selectedMap; 

    for (auto &directoryEntry : std::filesystem::directory_iterator("./maps"))
    {
        std::string fileName = directoryEntry.path().string();
        
        mapNames.push_back(fileName); 
    }

    for(int i=1; i<=totalMaps; i++)
    {
        std::cout << i << ") " << mapNames[i] << std::endl;    
    }
   
    std::cout << "Please enter the index number of one of the maps in the list above" << std::endl;

    std::cout << "There are currently " << totalMaps << " to choose from" <<  std::endl;  

    std::cin >> selectedMap;

    while(selectedMap < 1 || selectedMap > totalMaps)
    {
        std::cout << "Please try again, you can only chose from the list above" << std::endl; 

        std::cin >> selectedMap;
    }

    std::cout << "Loading the selected map..." << std::endl; 

    MapLoader::loadMap(mapNames[selectedMap]);


}

MapSelect::~MapSelect(){}


PlayerAmount::PlayerAmount()
{
    int totalPlayers;

    std::cout << "Please select the number of players in your game" << std::endl; 

    std::cin >> totalPlayers; 

    while(totalPlayers < 2 || totalPlayers > 5){
        
        std::cout << "Please try again. You can only choose 2-5 players" << std::endl; 

        std::cin >> totalPlayers; 
    }

    setPlayers(totalPlayers); 
} 

PlayerAmount::~PlayerAmount(){}

void PlayerAmount::setPlayers(int players)
{
    totalPlayers = players; 
}

int PlayerAmount::getPlayers()
{
    return totalPlayers; 
}

int main()
{
    PlayerAmount amount; 
    MapSelect maps; 
}