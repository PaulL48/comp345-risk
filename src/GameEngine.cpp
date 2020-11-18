#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
//#include "GameStartup.h"
//#include "MapObserver.h"


GameEngine::GameEngine()
{
    PlayerAmount amount; 
    MapSelect maps;  
    ControlObservers observers;

    //std::vector<Player> players= &GameStartup::getPlayers();
    //std::size_t players = players.size();   
    //std::cout << "There are currently " << players << " in the game" << std::endl;
}

GameEngine::~GameEngine(){}

MapSelect::MapSelect()
{
    for (auto &directoryEntry : std::filesystem::directory_iterator("./maps"))
    {
        std::string fileName = directoryEntry.path().string();
        mapNames.push_back(fileName); 
    }

    std::cout << "Maps Selection: " << std::endl; 
    std::cout << std::endl;

    for(std::size_t i=0; i<mapNames.size(); i++)
    {
        std::cout << (i+1) << ") " << mapNames[i] << std::endl;    
    }

    std::cout << std::endl; 
   
    std::cout << "Please enter the index number of one of the maps in the list above" << std::endl;

    std::cin >> selectedMap;

    while(selectedMap < 1 || selectedMap > mapNames.size())
    {
        std::cout << "Please try again, you can only chose from the list above" << std::endl; 

        std::cin >> selectedMap;
    }

    std::cout << "Loading the selected map..." << std::endl; 
    std::cout << std::endl;   
}

MapSelect::~MapSelect(){}

PlayerAmount::PlayerAmount()
{
    int totalPlayers;

    std::cout << "---------------------------------------------------------------" << std::endl;

    std::cout << "Please select the number of players in your game" << std::endl; 

    std::cin >> totalPlayers; 

    while(totalPlayers < 2 || totalPlayers > 5){
        
        std::cout << "Please try again. You can only choose 2-5 players" << std::endl; 

        std::cin >> totalPlayers; 
    }

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << std::endl; 

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

ControlObservers::ControlObservers()
{
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "Please select if you want the Phase observers ON or OFF" << std::endl; 
    std::cout << "1) Phase observers ON" << std::endl;
    std::cout << "2) Phase observers OFF" << std::endl;

    std::cin >> phaseObserver;

    while(phaseObserver < 1 || phaseObserver > 2)
    {
        std::cout << "Please try again, you can only choose between 1) On or 2) Off" << std::endl; 
        std::cin >> phaseObserver;
    }
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "Please select if you want the Game Statistic Observers ON or OFF" << std::endl; 
    std::cout << "1) Game Statistic Observers ON" << std::endl;
    std::cout << "2) Game Statistic Observers OFF" << std::endl;

    std::cin >> statObserver;

    while(statObserver < 1 || statObserver > 2)
    {
        std::cout << "Please try again, you can only choose between 1) On or 2) Off" << std::endl; 
        std::cin >> statObserver;
    }
    std::cout << "---------------------------------------------------------------" << std::endl;

    //Need to handle observers here

    // if(phaseObserver == 1)
    // {
    //     Map *model = new Map (MapLoader::createMap(mapNames[selectedMap-1])); 
    //     MapObserver *view = new MapObserver(model);
    //     MapContoller *contoller = new MapContoller(view, model);
    //     contoller->controlMap();
    //     delete view;
    //     delete model;
    //     delete contoller;
    // }

    //if(statObserver == 1) 
    //{
    //}
    
    std::ifstream input(mapNames[selectedMap-1]);
    std::vector<std::string> v = MapLoader::readFile(input);

    if(MapLoader::validateFile(v))
    {
        MapLoader::loadMap(mapNames[selectedMap-1]);
        Deck gameDeck;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "The selected map is invalid, please start again." << std::endl;
    }
    
    std::cout << "---------------------------------------------------------------" << std::endl;

    mapNames.clear();
}
    
ControlObservers::~ControlObservers(){}
