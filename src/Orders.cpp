#include "Orders.h"
#include <algorithm>
#include <random>
#include <functional>
#include <ctime>
using std::ostream;
using std::string;
using std::vector;

OrderDataPayload::OrderDataPayload() :
    player(nullptr),
    enemyPlayer(nullptr),
    numberOfArmies(new int(0)),
    sourceTerritory(nullptr),
    targetTerritory(nullptr)
{
}

OrderDataPayload::~OrderDataPayload()
{
    delete this->numberOfArmies;
}

OrdersList::OrdersList() : orders(new vector<Order *>())
{
}

OrdersList::OrdersList(const OrdersList &ordersList) :
    orders(clone(*ordersList.orders))
{
}

OrdersList::~OrdersList()
{
    for (std::size_t i = 0; i < orders->size(); ++i)
    { // deletes order pointers in the vector prior to deleting the vector
        delete orders->at(i);
    }
    delete this->orders;
}

OrdersList &OrdersList::operator=(const OrdersList &ordersList)
{
    if (this == &ordersList)
    {
        return *this;
    }

    polymorphicDeepCopy(*orders, *ordersList.orders);
    return *this;
}

ostream &operator<<(ostream &out, const OrdersList &ordersList)
{
    for (const Order *order : *ordersList.orders)
    {
        out << *order << "\n";
    }
    return out;
}

void OrdersList::addToList(const Order &order)
{
    orders->push_back(order.clone());
}

void OrdersList::move(const Order &order, int index)
{
    for (std::size_t i = 0; i < orders->size(); ++i)
    {
        if ((orders->at(i)->getUniqueId()) == (order.getUniqueId()))
        {
            Order *temp = orders->at(i);
            orders->erase(std::next(orders->cbegin(), i));
            orders->insert(std::next(orders->cbegin(), index), temp);
            break;
        }
    }
}

void OrdersList::moveToFront(const Order &order)
{
    this->move(order, 0);
}

void OrdersList::moveToEnd(const Order &order)
{
    this->move(order, orders->size() - 1);
}

void OrdersList::moveUp(const Order &order)
{
    vector<Order *>::iterator it =
        find_if(orders->begin(), orders->end(), [&order](const Order *q) {
            return q->getUniqueId() == order.getUniqueId();
        });

    if (it != orders->end())
    {
        int index = (it - orders->begin());
        if (index != 0)
        {
            this->move(order, index - 1);
        }
    }
}

void OrdersList::moveDown(const Order &order)
{
    vector<Order *>::iterator it =
        find_if(orders->begin(), orders->end(), [&order](const Order *q) {
            return q->getUniqueId() == order.getUniqueId();
        });

    if (it != orders->end())
    {
        int index = (it - orders->begin());
        if (static_cast<std::size_t>(index) != (orders->size() - 1))
        {
            this->move(order, index + 1);
        }
    }
}

void OrdersList::remove(const Order &order)
{
    for (auto it = orders->cbegin(); it != orders->cend(); ++it)
    {
        if (((*it)->getUniqueId()) == order.getUniqueId())
        {
            orders->erase(it);
            break;
        }
    }
}

const vector<Order *> &OrdersList::getList()
{
    return *orders;
}

int Order::counter = 0;

Order::Order(const Order &order) :
    uniqueId(new int(*order.uniqueId)),
    executed(new bool(*order.executed)),
    description(new std::string(*order.description)),
    effect(new std::string(*order.effect)),
    dataPayload(new OrderDataPayload(*order.dataPayload))
{
}

Order::~Order()
{
    delete this->description;
    delete this->effect;
    delete this->uniqueId;
    delete this->executed;
    delete this->dataPayload;
}

Order &Order::operator=(const Order &order)
{
    if (this == &order)
    {
        return *this;
    }

    description = new string(*order.description);
    effect = new string(*order.effect);
    executed = new bool(*order.executed);
    uniqueId = new int(counter++);
    dataPayload = new OrderDataPayload(*order.dataPayload);

    return *this;
}

Order::Order(const string &description, const string &effect) :
    uniqueId(new int(counter++)),
    description(new string(description)),
    effect(new string(effect)),
    dataPayload(new OrderDataPayload())
{
}

const string &Order::getDescription()
{
    return *description;
}

const string &Order::getEffect()
{
    return *effect;
}

void Order::setExecutedStatus(bool status)
{
    *executed = status;
}

const bool &Order::getExecutedStatus()
{
    return *executed;
}

int Order::getUniqueId() const
{
    return *uniqueId;
}

ostream &operator<<(ostream &out, const Order &order)
{
    out << *(order.description);
    if (*(order.executed))
    {
        out << " -> Effect: " << *(order.effect);
    };
    out << "\n";
    return out;
}

Deploy::Deploy(const Deploy &order) : Order(order)
{
}

Deploy &Deploy::operator=(const Deploy &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Deploy::Deploy() : Order("Deploy", "Deploy troops to a territory")
{
}

Deploy::~Deploy()
{
}

bool Deploy::validate(const Player* const player, const Player* const, const Territory* const targetTerritory, const Territory* const)
{
   return targetTerritory->getOwningPlayer() == &*player ? true : false;
}

void Deploy::execute(){
    this->execute(this->dataPayload->player, *this->dataPayload->numberOfArmies, this->dataPayload->targetTerritory, nullptr, nullptr);
}


void Deploy::execute(Player* player, int numberOfArmies, Territory* targetTerritory, Territory*, Player*)
{
    if(this->validate(player, nullptr, targetTerritory, nullptr)){
        targetTerritory->setOccupyingArmies(targetTerritory->getOccupyingArmies()+numberOfArmies);
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "\tInvalid order. Target territory does not belong to player." << std::endl;
    }
}

Order *Deploy::clone() const
{
    return new Deploy(*this);
}

Advance::Advance(const Advance &order) : Order(order)
{
}

Advance &Advance::operator=(const Advance &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Advance::Advance() : Order("Advance", "Advance troops to a neighbouring territory")
{
}

Advance::~Advance()
{
}

bool Advance::validate(const Player* const player, const Player* const, const Territory* const targetTerritory, const Territory* const sourceTerritory)
{
   if(sourceTerritory->getOwningPlayer() == &*player){
       if(targetTerritory->getOwningPlayer() != &*player){
           if(player->isNegotiator(targetTerritory->getOwningPlayer())){
               return false;
           }
       }
       return true;
   }
   return false;
}

void Advance::execute(){
    this->execute(this->dataPayload->player, *this->dataPayload->numberOfArmies, this->dataPayload->targetTerritory, this->dataPayload->sourceTerritory, nullptr);
}

void Advance::execute( Player* player, int numberOfArmies, Territory* targetTerritory, Territory* sourceTerritory, Player*)
{
    if(this->validate(player, nullptr, targetTerritory, sourceTerritory)){
        sourceTerritory->setOccupyingArmies(sourceTerritory->getOccupyingArmies()-numberOfArmies);
        if(targetTerritory->getOwningPlayer() == &*player){
            /*  Target territory belongs to player -> move from source to target */  
            targetTerritory->setOccupyingArmies(targetTerritory->getOccupyingArmies()+numberOfArmies);
        }
        else{
            /* Target territory belongs to enemy -> Attack */ 
            std::default_random_engine generator(static_cast<unsigned int>(time(0)));
            std::uniform_int_distribution<int> distribution(1,100);
            auto killProbability = std::bind( distribution, generator );
            int enemyTerritoryArmyUnits = targetTerritory->getOccupyingArmies();

            while(numberOfArmies != 0 && enemyTerritoryArmyUnits != 0){
                // player attacks
                // if kill probability <= 60, one defending army reduced
                if(killProbability() <= 60){
                    --enemyTerritoryArmyUnits;                                                
                }

                // enemy attacks
                // if kill probability <= 70, one attacking army reduced
                if(killProbability() <= 70){
                    --numberOfArmies;
                }
            } 

            if(numberOfArmies != 0){
                targetTerritory->setOwningPlayer(*player);
                targetTerritory->setOccupyingArmies(numberOfArmies);
            }
            else{
                targetTerritory->setOccupyingArmies(enemyTerritoryArmyUnits);
            }
        }
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "Invalid order. Source territory does not belong to player." << std::endl;
    }
}

Order *Advance::clone() const
{
    return new Advance(*this);
}

Bomb::Bomb(const Bomb &order) : Order(order)
{
}

Bomb &Bomb::operator=(const Bomb &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Bomb::Bomb() : Order("Bomb", "Bomb a territory")
{
}

Bomb::~Bomb()
{
}

bool Bomb::validate(const Player* const player, const Player* const, const Territory* const targetTerritory, const Territory* const)
{
    if(targetTerritory->getOwningPlayer() == &*player || (player->isNegotiator(targetTerritory->getOwningPlayer()))){
        return false;
    }

    return true;
}

void Bomb::execute()
{
    this->execute(this->dataPayload->player, 0, this->dataPayload->targetTerritory, nullptr, nullptr);
}

void Bomb::execute(Player* player, int, Territory* targetTerritory, Territory*, Player*)
{
    if(this->validate(player, nullptr, targetTerritory, nullptr)){
        targetTerritory->setOccupyingArmies((targetTerritory->getOccupyingArmies())/2);
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "\tInvalid order bomb." << std::endl;
    }    
}

Order *Bomb::clone() const
{
    return new Bomb(*this);
}

Blockade::Blockade(const Blockade &order) : Order(order)
{
}

Blockade &Blockade::operator=(const Blockade &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Blockade::Blockade() :
    Order("Blockade", "Seals a territory, Prevents people or goods from entering or "
                      "leaving the territory")
{
}

Blockade::~Blockade()
{
}

bool Blockade::validate(const Player* const player, const Player* const, const Territory* const targetTerritory, const Territory* const)
{
    return (targetTerritory->getOwningPlayer() == &*player) ? true : false;
}

void Blockade::execute()
{
    this->execute(this->dataPayload->player, 0, this->dataPayload->targetTerritory, nullptr, nullptr);
}

void Blockade::execute(Player *player, int, Territory* targetTerritory, Territory*, Player*)
{
    if(this->validate(player, nullptr, targetTerritory, nullptr)){
        Player* neutralPlayer = new Player("Neutral", vector<Territory>(), vector<Territory>(), Hand(), OrdersList(),0 , vector<int>());
        targetTerritory->setOccupyingArmies(targetTerritory->getOccupyingArmies()*2);
        targetTerritory->setOwningPlayer(*neutralPlayer);
        delete neutralPlayer;
        neutralPlayer = nullptr;
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "\tInvalid order. Territory does not belong to player." << std::endl;
    }
}

Order *Blockade::clone() const
{
    return new Blockade(*this);
}

Airlift::Airlift(const Airlift &order) : Order(order)
{
}

Airlift &Airlift::operator=(const Airlift &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Airlift::Airlift() : Order("Airlift", "Transport suplies or troops by air")
{
}

Airlift::~Airlift()
{
}

bool Airlift::validate(const Player* const player, const Player* const, const Territory* const targetTerritory, const Territory* const sourceTerritory)
{
   return ((targetTerritory->getOwningPlayer() == &*player) && (sourceTerritory->getOwningPlayer() == &*player))? true : false;
}

void Airlift::execute(){
    this->execute(this->dataPayload->player, *this->dataPayload->numberOfArmies, this->dataPayload->targetTerritory, this->dataPayload->sourceTerritory, nullptr);
}

void Airlift::execute(Player* player, int numberOfArmies, Territory* targetTerritory, Territory* sourceTerritory, Player*)
{
    if(this->validate(player, nullptr, targetTerritory, sourceTerritory)){
        sourceTerritory->setOccupyingArmies(sourceTerritory->getOccupyingArmies()-numberOfArmies);
        targetTerritory->setOccupyingArmies(targetTerritory->getOccupyingArmies()+numberOfArmies);
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "Invalid order. Can not airlift from or to enemy territory." << std::endl;
    }
}

Order *Airlift::clone() const
{
    return new Airlift(*this);
}

Negotiate::Negotiate(const Negotiate &order) : Order(order)
{
}

Negotiate &Negotiate::operator=(const Negotiate &order)
{
    if (&order == this)
    {
        return *this;
    }
    Order::operator=(order);
    return *this;
}

Negotiate::Negotiate() :
    Order("Negotiate", "Negotiate with the opposition to reach an agreement")
{
}

Negotiate::~Negotiate()
{
}

bool Negotiate::validate(const Player* const player, const Player* const enemyPlayer, const Territory* const, const Territory* const)
{
    return (&*player == &*enemyPlayer) ? false : true;
}

void Negotiate::execute()
{
    this->execute(this->dataPayload->player, 0, nullptr, nullptr, this->dataPayload->enemyPlayer);
}

// sets doNotAttack to true for the territores inside attack lists both for player and enemy where owner of territory equals the opposing party  
void Negotiate::execute(Player* player, int, Territory*, Territory*, Player* enemyPlayer)
{
    if(this->validate(player, enemyPlayer, nullptr, nullptr)){
        player->addToNegotiatorsList(enemyPlayer);
        enemyPlayer->addToNegotiatorsList(player);
        this->setExecutedStatus(true);
    }
    else{
        std::cout << "\tInvalid negotiation. Target player == player." << std::endl;
    }
}

Order *Negotiate::clone() const
{
    return new Negotiate(*this);
}