#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Map.h"

class PlayerStrategy
{
public:
    // Fill the order list of the player with orders based on the intended strategy behavior
    virtual void issueOrder(const Map& map, Player& player) = 0;

    // Return the list of territories to attack based on the intended strategy behavior
    virtual std::vector<Territory>& toAttack(const Map& map, Player& player) = 0;

    // Return the list of territories to reinforce based on the intended strategy behavior
    virtual std::vector<Territory>& toDefend(const Map& map, Player& player) = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, Player& player);
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, Player& player);
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, Player& player);
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, Player& player);
};

#endif
