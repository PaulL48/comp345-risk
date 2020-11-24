#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Map.h"

class PlayerStrategy
{
public:
    virtual void issueOrder() = 0;
    virtual std::vector<Territory>& toAttack() = 0;
    virtual std::vector<Territory>& toDefend() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder();
    virtual std::vector<Territory>& toAttack();
    virtual std::vector<Territory>& toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder();
    virtual std::vector<Territory>& toAttack();
    virtual std::vector<Territory>& toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder();
    virtual std::vector<Territory>& toAttack();
    virtual std::vector<Territory>& toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    virtual void issueOrder();
    virtual std::vector<Territory>& toAttack();
    virtual std::vector<Territory>& toDefend();
};

#endif
