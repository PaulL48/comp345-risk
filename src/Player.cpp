#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * This is the main constructor for the Player Class.
 * */
Player::Player(const std::string &playerName,
               const std::vector<Territory> &territoriesAttack,
               const std::vector<Territory> &territoriesDefend, const Hand &cards,
               const OrdersList &orders,const int& numArmies, const std::vector<int>& playerOrder) :
    playerName(new std::string(playerName)),
    territoriesAttack(new std::vector<Territory>(territoriesAttack)),
    territoriesDefend(new std::vector<Territory>(territoriesDefend)),
    cards(new Hand(cards)),
    orders(new OrdersList(orders)),
    numArmies(new int(numArmies)),
    playerOrder(new std::vector<int>(playerOrder))
{
}

Player::Player() :
    playerName(new std::string("")),
    territoriesAttack(new std::vector<Territory>),
    territoriesDefend(new std::vector<Territory>),
    cards(new Hand),
    orders(new OrdersList),
    numArmies(new int(0)),
    playerOrder(new std::vector<int>)
{
}
/**
 * This is the issueOrder method.
 * This method creates an Order and adds it to the players orders vector.
 * */
void Player::issueOrder()
{
    /**
     * As told by the teacher in class, she said it was ok to just create any type of
     * order for the meantime as their isn't a clear explanation in the assignment
     * concerning this part
     * */
    Bomb order;
    orders->addToList(order);
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
int &Player::getNumArmies(){
    return *numArmies;
}
std::vector<int>& Player::getPlayerOrder(){
    return *playerOrder;
}
bool Player::operator==(const Player& player) const
{
    return this->playerName == player.playerName;
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