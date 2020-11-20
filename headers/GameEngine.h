#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <string>
#include <unordered_set>
#include <typeindex>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"

extern int totalPlayers; 
extern std::size_t selectedMap;
extern int phaseObserver;
extern int statObserver; 
extern std::vector<std::string> mapNames;

enum class GamePhase
{
    REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS
};

void removeNewlines(std::string& string);

namespace ConfigurationUtilities
{
    std::vector<Player> getPlayers();
    void getPlayerNames(std::vector<Player>& players);
}

void GameInitialization(GameEngine& gameEngine);

// This number divides the number of territories a player owns
// to determine how many armies they receive

// STATELESS UTILITY FUNCTIONS

namespace GameLogic
{
    constexpr int MINIMUM_REINFORCEMENTS_PER_TURN = 3;
    constexpr double TERRITORY_TO_ARMY_DIVISOR = 3.0;

    int territoryArmyBonus(const Map& map, const Player& player);
    int continentArmyBonus(const Map& map, const Player& player);
    int totalArmyBonus(const Map& map, const Player& player);
    int playerTotalAvailableArmies(const Map& map, const Player& player);
    bool playerIsDefeated(const Map& map, const Player& player);
}

// This function packs an array with type information supplied via template
template <typename... Types>
void Fill(std::vector<std::type_index>& vec)
{
    vec.insert(vec.end(), {typeid(Types)...});
}

// Add the next order in a list that matches one of the selected types to a master list, following the supplied cursor. If the cursor is at the end of the container, nothing happens
void addNextPhasedOrderOrNothing(std::vector<Order*>& masterList, const std::vector<Order*>& playerList, std::vector<Order*>::const_iterator& cursor, const std::vector<std::type_index>& selectedTypes);

// Go one by one through the supplied players adding orders matching a set of types until all these orders are in a master queue
void fillRoundRobinOrders(std::vector<Order*> masterList, const std::vector<Player>& players, const std::vector<std::type_index>& selectedTypes);

class GameEngine : public Subject
{
public:
    GameEngine();
    ~GameEngine(); 
    // TODO: required methods
    //GameEngine(const Map& map, const std::vector<Player>& players);

    // Phase methods
    void configure();
    void mainGameLoop();
    void reinforcementPhase(Player& player);
    void issueOrdersPhase(Player& player);
    void executeOrdersPhase();

    // Methods based on current player
    const Player& getCurrentPlayer() const;
    std::vector<Territory> getCurrentPlayerOwnedTerritories() const;
    std::vector<Continent> getCurrentPlayerOwnedContinents() const;
    int getCurrentPlayerOwnedContinentControlBonus() const;
    int getCurrentPlayerTotalAvailableArmies() const;

    GamePhase getCurrentPhase() const;

    bool gameShouldEnd() const;
    void cullDefeatedPlayers();
private:
    bool* phaseObserver;
    bool* stateObserver;
    Map* map;
    std::vector<Player>* players;
    GamePhase* currentPhase;
    std::size_t* currentPlayer;
    Deck* deck; // TODO: Initialize
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
