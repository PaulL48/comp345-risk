#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include "Player.h"
#include "Map.h"
#include "Cards.h"

enum class GamePhase
{
    REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS
};


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



class GameEngine
{
public:
    // TODO: required methods
    GameEngine(const Map& map, const std::vector<Player>& players);

    // Phase methods
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

    Map* map;
    std::vector<Player>* players;
    GamePhase* currentPhase;
    std::size_t* currentPlayer;
    Deck* deck; // TODO: Initialize
};

#endif
