#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Map.h"

class PlayerStrategy
{
public:
    // Fill the order list of the player with orders based on the intended strategy behavior
    virtual void issueOrder(const Map& map, Player& player) = 0;

    // Return the list of territories to attack based on the intended strategy behavior
    virtual std::vector<Territory>& toAttack(const Map& map, const Player& player) = 0;

    // Return the list of territories to reinforce based on the intended strategy behavior
    virtual std::vector<Territory>& toDefend(const Map& map, const Player& player) = 0;

    virtual PlayerStrategy* clone() const = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, const Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, const Player& player);
    virtual PlayerStrategy* clone() const;
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, const Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, const Player& player);
    virtual PlayerStrategy* clone() const;
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, const Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, const Player& player);
    virtual PlayerStrategy* clone() const;
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder(const Map& map, Player& player);
    virtual std::vector<Territory>& toAttack(const Map& map, const Player& player);
    virtual std::vector<Territory>& toDefend(const Map& map, const Player& player);
    virtual PlayerStrategy* clone() const;
};

#endif
