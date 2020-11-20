#include "GameEngine.h"

#include <algorithm>
#include <functional>
#include <cmath>
#include <typeindex>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"

void removeNewlines(std::string& string)
{
    string.erase(remove(string.begin(), string.end(), '\n'), string.end());
    string.erase(remove(string.begin(), string.end(), '\r'), string.end());
}

std::vector<Player> ConfigurationUtilities::getPlayers()
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

    std::vector<Player> players(totalPlayers);
    ConfigurationUtilities::getPlayerNames(players);
    return players;
}

void ConfigurationUtilities::getPlayerNames(std::vector<Player>& players)
{
    std::size_t i = 0;
    for (auto& player : players)
    {
        std::string name;
        while (name.empty())
        {
            std::cout << "Player " << i + 1<< " set your name: ";
            std::getline(std::cin, name);
            removeNewlines(name);
            if (name.empty())
            {
                std::cout << "No input" << std::endl;
            }
        }
        player.setPlayerName(name);
        ++i;
    }
}



int GameLogic::territoryArmyBonus(const Map& map, const Player& player)
{
    std::vector<Territory> territoriesOwned = map.getPlayersTerritories(player);
    return static_cast<int>(std::floor(territoriesOwned.size() / GameLogic::TERRITORY_TO_ARMY_DIVISOR));
}

int GameLogic::continentArmyBonus(const Map& map, const Player& player)
{
    std::vector<Continent> continentsOwned = map.getPlayersContinents(player);
    int continentBonus = 0;
    for (const auto& continent : continentsOwned)
    {
        continentBonus += continent.getBonusArmyValue();
    }
    return continentBonus;
}

int GameLogic::totalArmyBonus(const Map& map, const Player& player)
{
    return std::max(GameLogic::territoryArmyBonus(map, player) + GameLogic::continentArmyBonus(map, player), GameLogic::MINIMUM_REINFORCEMENTS_PER_TURN);
}

int GameLogic::playerTotalAvailableArmies(const Map& map, const Player& player)
{
    std::vector<Territory> territories = map.getPlayersTerritories(player);
    int deployedArmies = 0;
    for (const auto& territory : territories)
    {
        deployedArmies += territory.getOccupyingArmies();
    }
    return deployedArmies + player.getReinforcementPool();
}

bool GameLogic::playerIsDefeated(const Map& map, const Player& player)
{
    return map.getPlayersTerritories(player).size() == 0;
}

void addNextPhasedOrderOrNothing(std::vector<Order*>& masterList, const std::vector<Order*>& playerList, std::vector<Order*>::const_iterator& cursor,  const std::vector<std::type_index>& selectedTypes)
{
    for (; cursor != playerList.end(); ++cursor)
    {
        if (std::find(selectedTypes.begin(), selectedTypes.end(), std::type_index(typeid(*cursor))) != selectedTypes.end())
        {
            masterList.push_back(*cursor);
            return;
        }
    }
}

void fillRoundRobinOrders(std::vector<Order*>& masterList, std::vector<Player>& players, const std::vector<std::type_index>& selectedTypes)
{
    std::vector<std::vector<Order*>::const_iterator> cursors;
    for (auto& player : players)
    {
        cursors.push_back(player.getOrders().getList().begin());
    }

    bool allListsScanned = false;
    while (!allListsScanned)
    {
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            addNextPhasedOrderOrNothing(masterList, players.at(i).getOrders().getList(), cursors.at(i), selectedTypes);
        }

        allListsScanned = true;
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            allListsScanned &= cursors.at(i) == players.at(i).getOrders().getList().end();
        }
    }
}

// GameEngine::GameEngine(const Map& map, const std::vector<Player>& players) : 
//     map(new Map(map)), 
//     players(new std::vector<Player>(players)), 
//     currentPhase(new GamePhase()), 
//     currentPlayer(new std::size_t())
// {}

GameEngine::GameEngine() :
    phaseObserver(nullptr),
    stateObserver(nullptr),
    map(nullptr),
    players(nullptr),
    currentPhase(nullptr),
    currentPlayer(nullptr)
{
}

void GameEngine::configure()
{

}

void GameEngine::mainGameLoop()
{
    while (!gameShouldEnd())
    {
        for (std::size_t i = 0; i < this->players->size(); ++i)
        {
            *this->currentPlayer = i;
            this->reinforcementPhase(this->players->at(i));
            this->issueOrdersPhase(this->players->at(i));
        }
        this->executeOrdersPhase();
        cullDefeatedPlayers();
    }
}

void GameEngine::reinforcementPhase(Player& player)
{
    *this->currentPhase = GamePhase::REINFORCEMENT;
    player.addArmies(GameLogic::totalArmyBonus(*this->map, player));
}

void GameEngine::issueOrdersPhase(Player& player)
{
    *this->currentPhase = GamePhase::ISSUE_ORDERS;
    player.issueOrder(*this->map);
}

void GameEngine::executeOrdersPhase()
{
    *this->currentPhase = GamePhase::EXECUTE_ORDERS;
    // TODO: Notify observer

    this->players->at(0).getOrders();

    std::vector<Order*> masterList;
    std::vector<std::type_index> deployPriority;
    Fill<Deploy>(deployPriority);
    fillRoundRobinOrders(masterList, *this->players, deployPriority);

    std::vector<std::type_index> airliftPriority;
    Fill<Airlift>(airliftPriority);
    fillRoundRobinOrders(masterList, *this->players, airliftPriority);

    std::vector<std::type_index> blockadePriority;
    Fill<Blockade>(blockadePriority);
    fillRoundRobinOrders(masterList, *this->players, blockadePriority);

    std::vector<std::type_index> remainingPriorities;
    Fill<Advance, Bomb, Airlift, Negotiate>(remainingPriorities);
    fillRoundRobinOrders(masterList, *this->players, remainingPriorities);

    // for (Order* order : masterList)
    // {
    //     // TODO: Print some stuff so the TA sees all deploys are executed first
    //     //order->execute();
    // }
}

const Player& GameEngine::getCurrentPlayer() const
{
    return this->players->at(*this->currentPlayer);
}

std::vector<Territory> GameEngine::getCurrentPlayerOwnedTerritories() const
{
    return this->map->getPlayersTerritoriesNonConst(this->players->at(*this->currentPlayer));
}

std::vector<Continent> GameEngine::getCurrentPlayerOwnedContinents() const
{
    return this->map->getPlayersContinents(this->getCurrentPlayer());
}

int GameEngine::getCurrentPlayerOwnedContinentControlBonus() const
{
    return GameLogic::continentArmyBonus(*this->map, this->getCurrentPlayer());
}

int GameEngine::getCurrentPlayerTotalAvailableArmies() const
{
    return GameLogic::playerTotalAvailableArmies(*this->map, this->getCurrentPlayer());
}

GamePhase GameEngine::getCurrentPhase() const
{
    return *this->currentPhase;
}

bool GameEngine::gameShouldEnd() const
{
    // If a player owns all the territories and defeated players are culled, 
    // only one player will remain
    return this->players->size() == 1;
}

void GameEngine::cullDefeatedPlayers()
{
    auto predicate = [this](const Player& p) { return GameLogic::playerIsDefeated(*map, p); };
    auto it = std::remove_if(this->players->begin(), this->players->end(), predicate);
    if (it != this->players->end())
    {
        this->players->erase(it);
    }
}

//#include "GameStartup.h"
//#include "MapObserver.h"

int totalPlayers = 0; 
std::size_t selectedMap;
int phaseObserver = 0;
int statObserver = 0; 
std::vector<std::string> mapNames = std::vector<std::string>(); 

// GameEngine::GameEngine()
// {
//     PlayerAmount amount; 
//     MapSelect maps;  
//     ControlObservers observers;

//     //std::vector<Player> players= &GameStartup::getPlayers();
//     //std::size_t players = players.size();   
//     //std::cout << "There are currently " << players << " in the game" << std::endl;
// }

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

    // ***  Handle observers here  ***

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
        //MapLoader::loadMap(mapNames[selectedMap-1]);
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


GameStartup::GameStartup(const int numPlayer, const Map &map) :
    numPlayers(new int(numPlayer)), map(new Map(map))
{
}
GameStartup::GameStartup() : numPlayers(0), map(new Map)
{
}
GameStartup::~GameStartup()
{
    delete numPlayers;
    //delete map;
    delete players;
    delete orderPlayers;
}
Map &GameStartup::getMap()
{
    return *map;
}

std::vector<Player> &GameStartup::getPlayers()
{
    return *players;
}

int GameStartup::getNumberOfArmies()
{
    switch (*numPlayers)
    {
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

void GameStartup::startupPhase()
{
    int numArmies = getNumberOfArmies();
    this->orderPlayers = new std::vector<int>((intitializeOrderPlayers(*numPlayers)));
    this->players = new std::vector<Player>(intializePlayers(numArmies));
    return;
}
std::vector<int> &GameStartup::intitializeOrderPlayers(const int numPlayers)
{
    std::vector<int> *orderPlayer = new std::vector<int>(numPlayers, -1);
    std::vector<int> numTerritoriesOwner = std::vector<int>(numPlayers, 0);
    for (int i = 0; i < numPlayers; i++)
    {
        numTerritoriesOwner.at(i) = i;
    }
    int index = 0;
    for (int i = 0; i < numPlayers; i++)
    {
        index = (rand() % numTerritoriesOwner.size());
        int val = numTerritoriesOwner.at(index);
        orderPlayer->at(i) = val;
        numTerritoriesOwner.erase(numTerritoriesOwner.begin() + index);
    }
    return *orderPlayer;
}

std::vector<Player> &GameStartup::intializePlayers(const int numArmies)
{
    Graph<Territory>& territories = map->getGraph();
    std::vector<Player> *playerList = new std::vector<Player>();
    std::vector<int> numTerritoriesOwned = std::vector<int>(*numPlayers, 0);
    int territoriesLeft = territories.size();
    int territoriesPerPlayer = territoriesLeft / (*numPlayers);
    for (int i = 0; i < *numPlayers; i++)
    {
        std::string *playerName = new std::string("Player " + std::to_string(i + 1));
        Hand hand;
        OrdersList orderlist;
        std::vector<Territory> *toAttack = new std::vector<Territory>();
        std::vector<Territory> *toDefend = new std::vector<Territory>();
        Player p = Player(*playerName, *toAttack, *toDefend, hand, orderlist, numArmies,
                          *orderPlayers);
        playerList->push_back(p);
    }
    int index = 0;
    std::vector<std::pair< Territory , const Player *>> changes;
    for (const Territory& territory : territories)
    {
        bool validInsert = true;

        while (validInsert)
        {
            index = (rand() % *numPlayers);
            if (territoriesLeft <= territoriesPerPlayer && territories.size() % *numPlayers != 0)
            {
                changes.push_back(std::make_pair(territory, &playerList->at(index)));
                validInsert = false;
                territoriesLeft--;
            }
            else
            {
                if (numTerritoriesOwned.at(index) != territoriesPerPlayer)
                {
                    int val = numTerritoriesOwned.at(index) + 1;
                    changes.push_back(
                        std::make_pair(territory, &playerList->at(index)));
                    numTerritoriesOwned.at(index) = val;
                    territoriesLeft--;
                    validInsert = false;
                }
            }
        }
    }
    for (auto &[territoryObj, playerObj] : changes)
    {
         map->setTerritoryOwner(territoryObj, *playerObj);
    }
    for (int i = 0; i < *numPlayers; i++)
    {
        Player player = playerList->at(i);
        std::vector<Territory> ownedTerritories = map->getPlayersTerritoriesNonConst(player);
        for (Territory territory : ownedTerritories)
        {
            std::unordered_set<Territory> neighborTerritories =
                *map->getNeighbors(territory);
            for (Territory neighborTerritory : neighborTerritories)
            {
                if (neighborTerritory.getOwningPlayer() != nullptr && *neighborTerritory.getOwningPlayer() != player)
                {
                    player.toDefend().push_back(territory);
                    if ((std::find(player.toAttack().begin(), player.toAttack().end(),
                                   neighborTerritory) == player.toAttack().end()))
                    {
                        player.toAttack().push_back(neighborTerritory);
                    }
                }
            }
        }
        playerList->at(i) = player;
    }
    return *playerList;
}
