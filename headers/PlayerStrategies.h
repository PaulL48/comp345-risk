#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Map.h"

class PlayerStrategy
{
public:
    virtual ~PlayerStrategy();

    // Fill the order list of the player with orders based on the intended strategy
    // behavior
    virtual void issueOrder(const Map &map, Player &player) = 0;

    // Return the list of territories to attack based on the intended strategy behavior
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player) = 0;

    // Return the list of territories to reinforce based on the intended strategy
    // behavior
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player) = 0;

    virtual PlayerStrategy *clone() const = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
    HumanPlayerStrategy();
    virtual ~HumanPlayerStrategy();
    virtual void issueOrder(const Map &map, Player &player);
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player);
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player);
    virtual PlayerStrategy *clone() const;
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    AggressivePlayerStrategy();
    virtual ~AggressivePlayerStrategy();
    virtual void issueOrder(const Map &map, Player &player);
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player);
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player);
    virtual PlayerStrategy *clone() const;
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    BenevolentPlayerStrategy();
    virtual ~BenevolentPlayerStrategy();
    virtual void issueOrder(const Map &map, Player &player);
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player);
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player);
    virtual PlayerStrategy *clone() const;
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    NeutralPlayerStrategy();
    virtual ~NeutralPlayerStrategy();
    virtual void issueOrder(const Map &map, Player &player);
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player);
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player);
    virtual PlayerStrategy *clone() const;
};

#endif
