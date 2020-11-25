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

enum class GamePhase
{
    REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS
};

namespace ConfigurationUtilities
{
    std::vector<Player> getPlayers();
    void getPlayerNames(std::vector<Player>& players);
    Map getMap();
    bool getPhaseObserverSwitch();
    bool getStatisticsObserverSwitch();
}

namespace StartupUtilities
{
    void shufflePlayers(std::vector<Player>& player);
    int startingArmies(int playerCount);
    void assignStartingArmies(std::vector<Player>& player);
    void assignTerritories(std::vector<Player>& players, Map& map);
    void playersDrawCards(std::vector<Player>& players, Deck& deck, int cardsPerHand);
}

namespace GameLogic
{
    constexpr int MINIMUM_REINFORCEMENTS_PER_TURN = 3;

    // Divides the number of territories a player owns
    // to determine how many armies they receive
    constexpr double TERRITORY_TO_ARMY_DIVISOR = 3.0;

    int territoryArmyBonus(const Map& map, const Player& player);
    int continentArmyBonus(const Map& map, const Player& player);
    int totalArmyBonus(const Map& map, const Player& player);
    int playerTotalAvailableArmies(const Map& map, const Player& player);
    bool playerIsDefeated(const Map& map, const Player& player);

    void addCardToConqueringPlayers(std::vector<Player>& players, Deck& deck);
}

// Packs an array with type information supplied via template
template <typename... Types>
void fill(std::vector<std::type_index>& vec)
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

    // Phase methods
    void configure();
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
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
    Deck* deck;
};

#endif
