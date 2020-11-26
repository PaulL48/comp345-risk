#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Map.h"
#include <iostream>

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

    HumanPlayerStrategy(const HumanPlayerStrategy &strategy);
    HumanPlayerStrategy &operator=(const HumanPlayerStrategy &strategy);
    friend std::ostream &operator<<(std::ostream &output, const HumanPlayerStrategy & strategy);

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
    AggressivePlayerStrategy(const AggressivePlayerStrategy &strategy);
    AggressivePlayerStrategy &operator=(const AggressivePlayerStrategy &strategy);
    friend std::ostream &operator<<(std::ostream &output, const AggressivePlayerStrategy & strategy);
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
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy &strategy);
    BenevolentPlayerStrategy &operator=(const BenevolentPlayerStrategy &strategy);
    friend std::ostream &operator<<(std::ostream &output, const BenevolentPlayerStrategy & strategy);
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
    NeutralPlayerStrategy(const NeutralPlayerStrategy &strategy);
    NeutralPlayerStrategy &operator=(const NeutralPlayerStrategy &strategy);
    friend std::ostream &operator<<(std::ostream &output, const NeutralPlayerStrategy & strategy);
    virtual void issueOrder(const Map &map, Player &player);
    virtual std::vector<Territory> toAttack(const Map &map, const Player &player);
    virtual std::vector<Territory> toDefend(const Map &map, const Player &player);
    virtual PlayerStrategy *clone() const;
};

#endif
