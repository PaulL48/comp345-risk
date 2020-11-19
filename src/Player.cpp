#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
               const OrdersList &orders,const int& numArmies, const std::vector<int>& playerOrder) :
    playerName(new std::string(playerName)),
    territoriesAttack(new std::vector<Territory>(territoriesAttack)),
    territoriesDefend(new std::vector<Territory>(territoriesDefend)),
    cards(new Hand(cards)),
    orders(new OrdersList(orders)),
    numArmies(new int(numArmies)),
    playerOrder(new std::vector<int>(playerOrder)),
    negotiators(new std::vector<Player*>),
    conqueredTerritory(new bool(false))
{
}

Player::Player() :
    playerName(new std::string("")),
    territoriesAttack(new std::vector<Territory>),
    territoriesDefend(new std::vector<Territory>),
    cards(new Hand),
    orders(new OrdersList),
    conqueredTerritory(new bool(false)),
    numArmies(new int),
    playerOrder(new std::vector<int>),
    negotiators(new std::vector<Player*>),
    conqueredTerritory(new bool(false))
{
}

void playerAddDeployOrder(Player&, const Map&)
{
    // Switch to toDefend
    //std::size_t choice = MenuUtilities::getValidatedNumericalChoice("Choose a territory to reinforce", map.getPlayersTerritories(player));

    // Create the deploy order
    // Preload the data payload
    //Deploy deploy;
    //deploy.getMutableDataPayload().targetTerritory

}

void Player::specifyDeploymentOrder(const Map&)
{
    // Switch to toDefend
    //std::size_t choice = MenuUtilities::getValidatedNumericalChoice("Choose a territory to reinforce", map.getPlayersTerritories(*this));

    // Create the deploy order
    // Preload the data payload
    //Deploy deploy;
    //deploy.getMutableDataPayload().targetTerritory

    //this->orders->addToList(deploy);
}

void Player::specifyOrderDeletion()
{
    std::size_t choice = MenuUtilities::getValidatedNumericalChoice("Choose an order to delete: ", this->getOrders().getList());
    this->getOrders().remove(*this->getOrders().getList().at(choice));
}

void Player::specifyAttackOrder(const Map&)
{
    //TODO: FILL IN
    // Present UI choices,
    // Get input
    // Create orders
    // load payload

    // OrderDataPayload payload;
    // payload.player = this;
    
    // payload.targetTerritory = &MenuUtilities::getMutableValidatedMenuChoice("Choose a territory to attack: ", this->toAttack());

    // Intersect the toDefend and targetTerritory neighbors
    // std::vector<Territory*> intersect;

    //auto& neighbors = map.
}

void Player::specifyDefendOrder()
{
    // TODO: FILL IN
    // Present UI choices,
    // Get input
    // Create orders
    // load payload
}

void Player::chooseCardToPlay()
{
    // TODO: FILL IN
    // Present UI choices,
    // Get input
    // Create orders
    // load payload
}

int Player::getReinforcementsPendingDeployment()
{
    return 1;
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
        std::cout << "Issue deployment orders to distribute all your reinforcements" << std::endl;
        std::cout << "Current orders are:" << std::endl;
        std::cout << this->orders << std::endl;

        MenuUtilities::executeMenuAction(
            "Actions: ",
            std::vector<std::string>{"Issue deploy order", "Delete deploy order"},
            std::vector<std::function<void(void)>>{std::bind(&Player::specifyDeploymentOrder, *this, map), std::bind(&Player::specifyOrderDeletion, *this)}
        );
    }

    // Issue attack and defense orders
    // OR at the same time play a card
    bool stopOrders = false;
    std::string exitString = "q";
    while (!stopOrders)
    {
        MenuUtilities::executeMenuActionWithExit(
            "Choose a type of order to create (Or stop creating orders by entering 'q'): ", 
            std::vector<std::string>{"Attack", "Defend", "Play a Card"},
            std::vector<std::function<void(void)>>{std::bind(&Player::specifyAttackOrder, *this, map), std::bind(&Player::specifyDefendOrder, *this), std::bind(&Player::chooseCardToPlay, *this)},
            exitString,
            stopOrders
        );
    }
}

Player::~Player()
{
    delete playerName;
    delete territoriesAttack;
    delete territoriesDefend;
    delete cards;
    delete orders;
    delete numArmies;
    delete playerOrder;
    delete negotiators;
    delete conqueredTerritory;
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
    numArmies = new int(*p.numArmies);
    playerOrder = new std::vector<int>(*p.playerOrder);
    negotiators = new std::vector<Player*>(*p.negotiators);
    conqueredTerritory = new bool(*p.conqueredTerritory);
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
    *this->negotiators = *player.negotiators;
    *this->conqueredTerritory = *player.conqueredTerritory;
    return *this;
}

bool Player::operator!=(const Player& player) const
{
    return !(*this == player);
}

std::vector<Territory> &Player::toAttack() const
{
    return *territoriesAttack;
}
std::vector<Territory> &Player::toDefend() const
{
    return *territoriesDefend;
}
Hand &Player::getCards()const
{
    return *cards;
}

OrdersList &Player::getOrders() const
{
    return *orders;
}

std::string &Player::getPlayerName()const
{
    return *playerName;
}

int &Player::getNumArmies() const{
    return *numArmies;
}
std::vector<int>& Player::getPlayerOrder() const {
    return *playerOrder;
}
bool Player::operator==(const Player& player) const
{
    return *this->playerName == *player.playerName;
}

void Player::addToNegotiatorsList(Player* player)const
{
    Player *ptr = player;
    this->negotiators->push_back(ptr);
}

bool Player::isNegotiator(const Player* player) const {
    for (auto it = (this->negotiators)->cbegin(); it != (this->negotiators)->cend(); ++it)
    {
        if (*it == player)
        {
            return true;
        }
    }
    return false;
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
    // TODO: fill in
    // stub
    add++;
}

int Player::getReinforcementPool() const
{
    // TODO: Fill in
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
