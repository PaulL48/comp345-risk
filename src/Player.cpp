#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void InputUtilities::removeNewlines(std::string &string)
{
    string.erase(remove(string.begin(), string.end(), '\n'), string.end());
    string.erase(remove(string.begin(), string.end(), '\r'), string.end());
}

std::size_t InputUtilities::getRangedInput(const std::string &prompt, std::size_t lower,
                                           std::size_t upper)
{
    bool invalidInput = true;
    std::string input;
    std::size_t parsedInput;
    while (invalidInput)
    {
        if (prompt.size() != 0)
        {
            std::cout << prompt << std::endl;
        }

        std::cout << "Please enter a value between " << lower << " and " << upper
                  << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            invalidInput = true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        try
        {
            invalidInput = false;
            parsedInput = std::stoull(input);
        }
        catch (const std::exception &e)
        {
            invalidInput = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (parsedInput < lower || parsedInput > upper)
        {
            invalidInput = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    return parsedInput;
}

Player::Player(const std::string &name, const PlayerStrategy &strategy) :
    playerName(new std::string(name)),
    cards(new Hand()),
    orders(new OrdersList()),
    reinforcementPool(new int(0)),
    negotiators(new std::vector<Player *>()),
    conqueredTerritory(new bool(false)),
    strategy(strategy.clone())
{
}

Player::Player(const Player &p) :
    playerName(new std::string(*p.playerName)),
    cards(new Hand(*p.cards)),
    orders(new OrdersList(*p.orders)),
    reinforcementPool(new int(*p.reinforcementPool)),
    negotiators(new std::vector<Player *>(*p.negotiators)),
    conqueredTerritory(new bool(*p.conqueredTerritory)),
    strategy(p.strategy->clone())
{
}

Player::Player() :
    playerName(new std::string("")),
    cards(new Hand()),
    orders(new OrdersList()),
    reinforcementPool(new int(0)),
    negotiators(new std::vector<Player *>()),
    conqueredTerritory(new bool(false)),
    strategy(nullptr)
{
}

Player::~Player()
{
    delete orders;
    delete playerName;
    delete cards;
    delete negotiators;
    delete conqueredTerritory;
    delete reinforcementPool;
    delete strategy;
}

bool Player::operator==(const Player &player) const
{
    return *this->playerName == *player.playerName;
}

bool Player::operator!=(const Player &player) const
{
    return !(*this == player);
}

Player &Player::operator=(const Player &player)
{
    if (this == &player)
        return *this;

    *this->playerName = *player.playerName;
    *this->cards = *player.cards;
    *this->orders = *player.orders;
    *this->negotiators = *player.negotiators;
    *this->conqueredTerritory = *player.conqueredTerritory;
    *this->reinforcementPool = *player.reinforcementPool;
    *this->strategy = *player.strategy;
    return *this;
}

std::ostream &operator<<(std::ostream &output, const Player &p)
{
    output << "(Player Name: " << *p.playerName << ", Reinforcement Pool: "
           << *p.reinforcementPool
           //<< ", Orders: " << *p.orders << ", Cards: " << *p.cards << ")";
           << ", Cards: " << *p.cards << ")";
    return output;
}

Hand &Player::getCards() const
{
    return *cards;
}

OrdersList &Player::getOrders() const
{
    return *orders;
}

const std::string &Player::getPlayerName() const
{
    return *playerName;
}

void Player::setPlayerName(const std::string &name)
{
    *this->playerName = name;
}

int Player::getReinforcementPool() const
{
    return *this->reinforcementPool;
}

void Player::addArmies(int add)
{
    *this->reinforcementPool += add;
}

bool Player::getConqueredTerritory() const
{
    return *this->conqueredTerritory;
}

void Player::setConqueredTerritory(bool conqueredTerritory)
{
    *this->conqueredTerritory = conqueredTerritory;
}

void Player::setStrategy(const PlayerStrategy &strategy)
{
    *this->strategy = strategy;
}

std::vector<Territory> Player::toAttack(const Map &map) const
{
    return this->strategy->toAttack(map, *this);
}

std::vector<Territory> Player::toDefend(const Map &map) const
{
    return this->strategy->toDefend(map, *this);
}

void Player::issueOrder(const Map &map)
{
    this->strategy->issueOrder(map, *this);
}

int Player::getReinforcementsPendingDeployment()
{
    int pendingDeployment = 0;
    for (Order *order : this->orders->getList())
    {
        if (typeid(order) == typeid(Deploy))
        {
            pendingDeployment += *order->getMutableDataPayload().numberOfArmies;
        }
    }
    return pendingDeployment;
}

void Player::addToNegotiatorsList(Player *player) const
{
    this->negotiators->push_back(player);
}

bool Player::isNegotiator(const Player *player) const
{
    for (auto it = (this->negotiators)->cbegin(); it != (this->negotiators)->cend();
         ++it)
    {
        if (*it == player)
        {
            return true;
        }
    }
    return false;
}
