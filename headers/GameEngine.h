#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_set>
#include <vector>

enum class GamePhase
{
    REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS
};

std::ostream &operator<<(std::ostream &output, const GamePhase& gamePhase);

namespace ConfigurationUtilities
{
    std::vector<Player> getPlayers();
    void getPlayerNames(std::vector<Player> &players);
    void getPlayerStrategies(std::vector<Player> &players);
    Map getMap();
    bool getPhaseObserverSwitch();
    bool getStatisticsObserverSwitch();

} // namespace ConfigurationUtilities

namespace StartupUtilities
{
    void shufflePlayers(std::vector<Player> &player);
    int startingArmies(int playerCount);
    void assignStartingArmies(std::vector<Player> &player);
    void assignTerritories(std::vector<Player> &players, Map &map);
    void playersDrawCards(std::vector<Player> &players, Deck &deck, int cardsPerHand);
} // namespace StartupUtilities

namespace GameLogic
{
    constexpr int MINIMUM_REINFORCEMENTS_PER_TURN = 3;

    // Divides the number of territories a player owns
    // to determine how many armies they receive
    constexpr double TERRITORY_TO_ARMY_DIVISOR = 3.0;

    int territoryArmyBonus(const Map &map, const Player &player);
    int continentArmyBonus(const Map &map, const Player &player);
    int totalArmyBonus(const Map &map, const Player &player);
    int playerTotalAvailableArmies(const Map &map, const Player &player);
    bool playerIsDefeated(const Map &map, const Player &player);

    void addCardToConqueringPlayers(std::vector<Player> &players, Deck &deck);

    // Given a collection of players containing orders lists, construct a linear list of
    // orders to execute based on the order of execution
    std::vector<Order *>
    constructMasterExecutionList(const std::vector<Player> &players);

    // Push the next order following cursor, with supplied execution priority, to the
    // master list
    void addExecutionPriorityOrderToMaster(std::vector<Order *> &masterList,
                                           const std::vector<Order *> &playerOrders,
                                           std::vector<Order *>::const_iterator &cursor,
                                           int executionPriority);

    // Iterate through supplied players, adding orders matching an execution priority,
    // until all these orders are in a master list
    void fillRoundRobinOrders(std::vector<Order *> &masterList,
                              const std::vector<Player> &players,
                              int executionPriority);
} // namespace GameLogic

class GameEngine : public Subject
{
public:

    // Construction / Destruction =========================================
    GameEngine();
    GameEngine(const GameEngine& gameEngine);
    ~GameEngine();

    // Operators ==========================================================
    GameEngine &operator=(const GameEngine &gameEngine);
    friend std::ostream &operator<<(std::ostream &output, const GameEngine &gameEngine);

    // Getters / Setters ==================================================
    const Player &getCurrentPlayer() const;
    GamePhase getCurrentPhase() const;
    const std::vector<Player> &getPlayers() const;
    const Map &getMap() const;
    Deck &getDeck();

    // Phase methods ======================================================
    void configure();
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    // Auxiliary Methods ==================================================
    bool gameShouldEnd() const;
    void cullDefeatedPlayers();

private:
    bool *phaseObserver;
    bool *stateObserver;
    Map *map;
    std::vector<Player> *players;
    GamePhase *currentPhase;
    std::size_t *currentPlayer;
    Deck *deck;
};

#endif
