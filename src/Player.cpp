#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void InputUtilities::clearTerminal()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

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

        std::cout << "Enter a value between " << lower << " and " << upper << ": ";

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

void InputUtilities::executeMenuAction(const std::string &prompt, const std::vector<std::string> &list, const std::vector<std::function<void(void)>> &actions)
{
    if (list.size() == 0)
    {
        return;
    }

    // Build the list string into the prompt
    std::stringstream ss;
    ss << prompt << std::endl;
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        ss << i + 1 << ") " << list.at(i) << std::endl;
    }

    actions.at(InputUtilities::getRangedInput(ss.str(), 1, list.size()) - 1)();
}

Player::Player(const std::string &name, const PlayerStrategy &strategy) :
    playerName(new std::string(name)),
    cards(new Hand()),
    orders(new OrdersList()),
    reinforcementPool(new int(0)),
    negotiators(new std::vector<Player *>()),
    conqueredTerritory(new bool(false)),
    strategy(strategy.clone()),
    engine(nullptr)
{
}

Player::Player(const Player &p) :
    playerName(new std::string(*p.playerName)),
    cards(new Hand(*p.cards)),
    orders(new OrdersList(*p.orders)),
    reinforcementPool(new int(*p.reinforcementPool)),
    negotiators(new std::vector<Player *>(*p.negotiators)),
    conqueredTerritory(new bool(*p.conqueredTerritory)),
    strategy(nullptr),
    engine(p.engine)
{
    if (p.strategy != nullptr)
    {
        this->strategy = p.strategy->clone();
    }
    else
    {
        this->strategy = new NeutralPlayerStrategy();
    }
}

Player::Player() :
    playerName(new std::string("")),
    cards(new Hand()),
    orders(new OrdersList()),
    reinforcementPool(new int(0)),
    negotiators(new std::vector<Player *>()),
    conqueredTerritory(new bool(false)),
    strategy(new NeutralPlayerStrategy()),
    engine(nullptr)
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

bool operator!=(const Player &lhs, const Player& rhs)
{
    return !(lhs == rhs);
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
    this->setStrategy(*player.strategy);
    //*this->strategy = *player.strategy;
    this->engine = player.engine;
    return *this;
}

std::ostream &operator<<(std::ostream &output, const Player &p)
{
    output << "(Name: " << *p.playerName << ", Strategy: " << *p.strategy << ", Reinforcement Pool: "
           << *p.reinforcementPool << ")";
           //<< ", Orders: " << *p.orders << ", Cards: " << *p.cards << ")";
           //<< ", Cards: " << *p.cards << ")";
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
    if (this->strategy != nullptr)
    {
        delete this->strategy;
    }

    this->strategy = strategy.clone();
}

std::vector<Territory> Player::toAttack(const Map &map) const
{
    return this->strategy->toAttack(map, *this);
}

std::vector<Territory> Player::toDefend(const Map &map) const
{
    return this->strategy->toDefend(map, *this);
}

void Player::issueOrder(Map &map)
{
    this->strategy->issueOrder(map, *this);
}

int Player::getReinforcementsPendingDeployment() const
{
    int pendingDeployment = 0;
    for (Order *order : this->orders->getList())
    {
        if (order->getExecutionPriority() == DEPLOY_PRIORITY)
        {
            pendingDeployment += *order->getDataPayload().numberOfArmies;
        }
    }
    return pendingDeployment;
}

int Player::getReinforcementsPendingDeployment(const Territory& territory) const
{
    int pendingDeployment = 0;
    for (const Order *order : this->orders->getList())
    {
        if ((order->getExecutionPriority() == DEPLOY_PRIORITY) && *order->getDataPayload().targetTerritory == territory)
        {
            pendingDeployment += *order->getDataPayload().numberOfArmies;
        }
        else if (order->getExecutionPriority() == REMAINDER_PRIORITY && order->getDataPayload().sourceTerritory != nullptr && order->getDataPayload().targetTerritory != nullptr && *order->getDataPayload().sourceTerritory == territory)
        {
            pendingDeployment -= *order->getDataPayload().numberOfArmies;
        }
        else if (order->getExecutionPriority() == AIRLIFT_PRIORITY && *order->getDataPayload().sourceTerritory == territory)
        {
            pendingDeployment -= *order->getDataPayload().numberOfArmies;
        }
        else if ((order->getExecutionPriority() == AIRLIFT_PRIORITY) && *order->getDataPayload().targetTerritory == territory)
        {
            pendingDeployment += *order->getDataPayload().numberOfArmies;
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

void Player::setGameEngine(GameEngine *engine)
{
    this->engine = engine;
}

GameEngine &Player::getGameEngine() const
{
    return *this->engine;
}

PlayerStrategy &Player::getStrategy() const
{
    return *this->strategy;
}

std::vector<Territory> Player::getWeakest(const std::vector<Territory> &territories) const
{
    std::vector<Territory> result;
    int min = std::numeric_limits<int>::max();
    for (const auto &territory : territories)
    {
        int actualArmyValue = territory.getOccupyingArmies() + this->getReinforcementsPendingDeployment(territory);
        if (actualArmyValue == min)
        {
            result.push_back(territory);
        }
        else if (actualArmyValue < min)
        {
            result.clear();
            result.push_back(territory);
            min = actualArmyValue;
        }
    }
    return result;
}

std::vector<Territory> Player::getStrongest(const std::vector<Territory> &territories) const
{
    std::vector<Territory> result;
    int max = 0;
    for (const auto &territory : territories)
    {
        int actualArmyValue = territory.getOccupyingArmies() + this->getReinforcementsPendingDeployment(territory);
        if (actualArmyValue == max)
        {
            result.push_back(territory);
        }
        else if (actualArmyValue > max)
        {
            result.clear();
            result.push_back(territory);
            max = actualArmyValue;
        }
    }
    return result;
}
