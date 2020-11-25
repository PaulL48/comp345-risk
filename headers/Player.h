#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategies.h"
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Hand;
class OrdersList;

class Player
{
public:
    // Construction / Destruction =========================================
    // Construct a players with an empty hand and orders list
    Player(const std::string &name, const PlayerStrategy &strategy);
    Player(const Player &player);
    ~Player();

    // Operators ==========================================================
    bool operator==(const Player &player) const;
    bool operator!=(const Player &player) const;
    Player &operator=(const Player &player);
    friend std::ostream &operator<<(std::ostream &output, const Player &player);

    // Getters / Setters ==================================================
    Hand &getCards() const;
    OrdersList &getOrders() const;
    const std::string &getPlayerName() const;
    void setPlayerName(const std::string &name);
    int getReinforcementPool() const;
    void addArmies(int add);
    bool getConqueredTerritory() const;
    void setConqueredTerritory(bool conqueredTerritory);
    void setStrategy(const PlayerStrategy &strategy);

    // Core Functionality =================================================
    std::vector<Territory> &toAttack(const Map &map) const;
    std::vector<Territory> &toDefend(const Map &map) const;
    void issueOrder(const Map &map);

    // Auxiliary Methods ==================================================
    // Return the number of armies currently queued to deploy
    int getReinforcementsPendingDeployment();
    void addToNegotiatorsList(Player *player) const;
    bool isNegotiator(const Player *player) const;

private:
    std::string *playerName;
    Hand *cards;
    OrdersList *orders;
    int *reinforcementPool;
    std::vector<Player *> *negotiators;
    bool *conqueredTerritory; // whether this player has conquered a territory this turn
    PlayerStrategy *strategy;
};

#endif
