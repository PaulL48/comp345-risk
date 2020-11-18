#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>

Player::Player(const std::string& name) : 
    playerName(new std::string(name)),     
    territoriesAttack(new std::vector<Territory>()),
    territoriesDefend(new std::vector<Territory>()),
    cards(new Hand()),
    orders(new OrdersList()),
    conqueredTerritory(new bool(false))
{
}

/**
 * This is the main constructor for the Player Class.
 * */
Player::Player(const std::string &playerName,
               const std::vector<Territory> &territoriesAttack,
               const std::vector<Territory> &territoriesDefend, const Hand &cards,
               const OrdersList &orders) :
    playerName(new std::string(playerName)),
    territoriesAttack(new std::vector<Territory>(territoriesAttack)),
    territoriesDefend(new std::vector<Territory>(territoriesDefend)),
    cards(new Hand(cards)),
    orders(new OrdersList(orders)),
    conqueredTerritory(new bool(false))
{
}

Player::Player() :
    playerName(new std::string("")),
    territoriesAttack(new std::vector<Territory>),
    territoriesDefend(new std::vector<Territory>),
    cards(new Hand),
    orders(new OrdersList),
    conqueredTerritory(new bool(false))
{
}

void playerAddDeployOrder(Player& player, const Map& map)
{
    // Switch to toDefend
    std::size_t choice = MenuUtilities::getValidatedNumericalChoice("Choose a territory to reinforce", map.getPlayersTerritories(player));

    // Create the deploy order
    // Preload the data payload

}

void playerDeleteOrder(Player& player)
{
    std::size_t choice = MenuUtilities::getValidatedNumericalChoice("Choose an order to delete: ", player.getOrders().getList());

}

/**
 * This is the issueOrder method.
 * This method creates an Order and adds it to the players orders vector.
 * */
void Player::issueOrder(const Map& map)
{
    // Issue deploy orders until all reinforcements are deployed
    while (this->getReinforcementsPendingDeployment() < *this->reinforcementPool)
    {
        std::cout << "Issue deployment orders to distribute your reinforcements" << std::endl;
        std::cout << "Current orders are:" << std::endl;
        std::cout << this->orders << std::endl;

        MenuUtilities::executeMenuAction(
            "Actions: ",
            std::vector<std::string>{"Issue deploy order", "Delete deploy order"},
            std::vector<std::function<void(void)>>{std::bind(&Player::specifyDeploymentOrder, *this, map), std::bind(playerDeleteOrder, *this)}
        );
    }

    // Issue attack and defense orders
    // OR at the same time play a card
    bool stopOrders = false;
    while (!stopOrders)
    {
        MenuUtilities::getValidatedNumericalChoiceWithExit("")
    }
}

Player::~Player()
{
    delete playerName;
    delete territoriesAttack;
    delete territoriesDefend;
    delete cards;
    delete orders;
}

/**
 * This is the copy constructor that takes in a Player object and creates a new Player
 * */
Player::Player(const Player &p)
{
    playerName = new std::string(*p.playerName);
    territoriesAttack = new std::vector<Territory>(*p.territoriesAttack);
    territoriesDefend = new std::vector<Territory>(*p.territoriesDefend);
    cards = new Hand(*p.cards);
    orders = new OrdersList(*p.orders);
}
/**
 * This is the assignment operator for the Player object
 *
 * */
Player &Player::operator=(const Player &player)
{
    if (this == &player)
        return *this;

    *this->playerName = *player.playerName;
    *this->territoriesAttack = *player.territoriesAttack;
    *this->territoriesDefend = *player.territoriesDefend;
    *this->cards = *player.cards;
    *this->orders = *player.orders;
    return *this;
}

bool Player::operator==(const Player& player) const
{
    return *this->playerName == *player.playerName;
}

bool Player::operator!=(const Player& player) const
{
    return !(*this == player);
}

std::vector<Territory> &Player::toAttack()
{
    return *territoriesAttack;
}
std::vector<Territory> &Player::toDefend()
{
    return *territoriesDefend;
}
Hand &Player::getCards()
{
    return *cards;
}

OrdersList &Player::getOrders()
{
    return *orders;
}

std::string &Player::getPlayerName()
{
    return *playerName;
}
/**
 * This is the stream insertion operator
 * */
std::ostream &operator<<(std::ostream &output, const Player &p)
{
    output << "( Player Name: " << *p.playerName << ", Orders : " << *p.orders;
    output << "Territories Attack: ";
    for (const auto &territory : *p.territoriesAttack)
    {
        output << territory << ",";
    }
    output << "Territories Defend: ";
    for (const auto &territory : *p.territoriesDefend)
    {
        output << territory << ",";
    }
    output << "Cards : " << *p.cards;
    output << ")";
    return output;
}

void Player::addArmies(int add)
{
    // stub
    add++;
}

int Player::getReinforcementPool() const
{
    return 10;
}

void Player::setConqueredTerritory(bool conqueredTerritory)
{
    *this->conqueredTerritory = conqueredTerritory;
}

bool Player::getConqueredTerritory() const
{
    return *this->conqueredTerritory;
}
