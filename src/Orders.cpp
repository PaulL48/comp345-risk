#include "Orders.h"
#include <algorithm>
#include <ctime>
#include <functional>
#include <random>
using std::ostream;
using std::string;
using std::vector;

OrderDataPayload::OrderDataPayload() :
    player(nullptr),
    enemyPlayer(nullptr),
    numberOfArmies(new int(0)),
    sourceTerritory(nullptr),
    targetTerritory(nullptr),
    map(nullptr)
{
}

OrderDataPayload::OrderDataPayload(const OrderDataPayload &odp) :
    player(odp.player),
    enemyPlayer(odp.enemyPlayer),
    numberOfArmies(new int(*odp.numberOfArmies)),
    sourceTerritory(odp.sourceTerritory),
    targetTerritory(odp.targetTerritory),
    map(odp.map)
{
}

OrderDataPayload::~OrderDataPayload()
{
    delete this->numberOfArmies;
}

OrderDataPayload &OrderDataPayload::operator=(const OrderDataPayload &odp)
{
    if (&odp == this)
    {
        return *this;
    }

    this->player = odp.player;
    this->enemyPlayer = odp.enemyPlayer;
    *this->numberOfArmies = *odp.numberOfArmies;
    this->sourceTerritory = odp.sourceTerritory;
    this->targetTerritory = odp.targetTerritory;
    this->map = odp.map;
    return *this;
}

//============================================================================================================================================================
// CLASS DEFINITIONS: OrdersList
//============================================================================================================================================================

OrdersList::OrdersList() : orders(new vector<Order *>())
{
}

OrdersList::OrdersList(const OrdersList &ordersList) : orders(clone(*ordersList.orders))
{
}

OrdersList::~OrdersList()
{
    for (auto *order : *this->orders)
    {
        delete order;
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

//============================================================================================================================================================
// CLASS DEFINITIONS: Order
//============================================================================================================================================================

int Order::counter = 0;

Order::Order(const string &description, const string &effect, int executionPriority) :
    uniqueId(new int(counter++)),
    executed(new bool(false)),
    description(new string(description)),
    effect(new string(effect)),
    dataPayload(new OrderDataPayload()),
    executionPriority(new int(executionPriority))
{
}

Order::Order(const Order &order) :
    uniqueId(new int(*order.uniqueId)),
    executed(new bool(*order.executed)),
    description(new std::string(*order.description)),
    effect(new std::string(*order.effect)),
    dataPayload(new OrderDataPayload(*order.dataPayload)),
    executionPriority(new int(*order.executionPriority))
{
}

Order::~Order()
{
    delete this->description;
    delete this->effect;
    delete this->uniqueId;
    delete this->executed;
    delete this->dataPayload;
    delete this->executionPriority;
}

Order &Order::operator=(const Order &order)
{
    if (this == &order)
    {
        return *this;
    }

    *description = *order.description;
    *effect = *order.effect;
    *executed = *order.executed;
    *uniqueId = *order.uniqueId;
    *dataPayload = *order.dataPayload;
    *executionPriority = *order.executionPriority;

    return *this;
}

const string &Order::getDescription()
{
    return *description;
}

const string &Order::getEffect()
{
    return *effect;
}

int Order::getExecutionPriority() const
{
    return *executionPriority;
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

OrderDataPayload &Order::getMutableDataPayload()
{
    return *this->dataPayload;
}

ostream &operator<<(ostream &out, const Order &order)
{
    out << *order.description << std::endl;
    out << "Issuing player: " << *order.dataPayload->player << std::endl;
    if (*(order.executed))
    {
        out << " -> Effect: " << *(order.effect);
    };
    out << "\n";
    return out;
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Deploy
//============================================================================================================================================================

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

Deploy::Deploy() : Order("Deploy", "Deploy troops to a territory", DEPLOY_PRIORITY)
{
}

Deploy::~Deploy()
{
}

bool Deploy::validate()
{
    if (this->dataPayload->targetTerritory == nullptr ||
        this->dataPayload->player == nullptr || this->dataPayload->map != nullptr)
    {
        return false;
    }

    return *this->dataPayload->targetTerritory->getOwningPlayer() ==
           *this->dataPayload->player;
}

void Deploy::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Target territory does not belong to player."
                  << std::endl;
        return;
    }

    Territory copy = *this->dataPayload->targetTerritory;
    copy.addArmies(*this->dataPayload->numberOfArmies);
    this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory, copy);
    this->setExecutedStatus(true);
}

Order *Deploy::clone() const
{
    return new Deploy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Advance
//============================================================================================================================================================

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

Advance::Advance() :
    Order("Advance", "Advance troops to a neighbouring territory", REMAINDER_PRIORITY)
{
}

Advance::~Advance()
{
}

bool Advance::validate()
{
    if (this->dataPayload->sourceTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->targetTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->map == nullptr)
    {
        return false;
    }

    // No offensive advance on players in negotiation
    if (*this->dataPayload->targetTerritory->getOwningPlayer() !=
            *this->dataPayload->sourceTerritory->getOwningPlayer() &&
        this->dataPayload->player->isNegotiator(
            this->dataPayload->targetTerritory->getOwningPlayer()))
    {
        return false;
    }

    return true;
}

void Advance::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Source territory does not belong to player."
                  << std::endl;
        return;
    }

    Territory copy = *this->dataPayload->sourceTerritory;
    copy.addArmies(-*this->dataPayload->numberOfArmies);
    this->dataPayload->map->updateTerritory(*this->dataPayload->sourceTerritory, copy);

    // Reinforcing territory
    if (this->dataPayload->sourceTerritory->getOwningPlayer() ==
        this->dataPayload->targetTerritory->getOwningPlayer())
    {
        this->dataPayload->targetTerritory->addArmies(
            *this->dataPayload->numberOfArmies);
        return;
    }

    // Attacking territory
    std::default_random_engine generator(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<int> distribution(1, 100);
    auto killProbability = std::bind(distribution, generator);
    int attackingArmies = *this->dataPayload->numberOfArmies;
    int defendingArmies = this->dataPayload->targetTerritory->getOccupyingArmies();

    while (attackingArmies != 0 && defendingArmies != 0)
    {
        // player attacks
        // if kill probability <= 60, one defending army reduced
        if (killProbability() <= 60)
        {
            --defendingArmies;
        }

        // enemy attacks
        // if kill probability <= 70, one attacking army reduced
        if (killProbability() <= 70)
        {
            --attackingArmies;
        }
    }

    if (attackingArmies != 0)
    {
        Territory copy = *this->dataPayload->targetTerritory;
        copy.setOwningPlayer(*this->dataPayload->player);
        copy.setOccupyingArmies(attackingArmies);
        this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory,
                                                copy);
    }
    else
    {
        Territory copy = *this->dataPayload->targetTerritory;
        copy.setOccupyingArmies(defendingArmies);
        this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory,
                                                copy);
    }
    this->setExecutedStatus(true);
}

Order *Advance::clone() const
{
    return new Advance(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Bomb
//============================================================================================================================================================

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

Bomb::Bomb() : Order("Bomb", "Bomb a territory", REMAINDER_PRIORITY)
{
}

Bomb::~Bomb()
{
}

bool Bomb::validate()
{
    if (this->dataPayload->sourceTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->targetTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->map == nullptr)
    {
        return false;
    }

    if (this->dataPayload->player->isNegotiator(
            this->dataPayload->targetTerritory->getOwningPlayer()))
    {
        return false;
    }

    if (*this->dataPayload->targetTerritory->getOwningPlayer() ==
        *this->dataPayload->player)
    {
        return false;
    }

    return true;
}

void Bomb::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid bomb order" << std::endl;
        return;
    }

    Territory copy = *this->dataPayload->targetTerritory;
    copy.setOccupyingArmies(copy.getOccupyingArmies() / 2);
    this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory, copy);
    this->setExecutedStatus(true);
}

Order *Bomb::clone() const
{
    return new Bomb(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Blockade
//============================================================================================================================================================

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
    Order("Blockade",
          "Seals a territory, Prevents people or goods from entering or leaving the "
          "territory",
          BLOCKADE_PRIORITY)
{
}

Blockade::~Blockade()
{
}

bool Blockade::validate()
{
    if (this->dataPayload->targetTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->map == nullptr)
    {
        return false;
    }

    return *this->dataPayload->targetTerritory->getOwningPlayer() ==
           *this->dataPayload->player;
}

void Blockade::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Territory does not belong to player." << std::endl;
        return;
    }

    Territory copy = *this->dataPayload->targetTerritory;
    copy.setOccupyingArmies(copy.getOccupyingArmies() * 2);
    copy.unsetOwningPlayer();
    this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory, copy);
    this->setExecutedStatus(true);
}

Order *Blockade::clone() const
{
    return new Blockade(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Airlift
//============================================================================================================================================================

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

Airlift::Airlift() :
    Order("Airlift", "Transport suplies or troops by air", AIRLIFT_PRIORITY)
{
}

Airlift::~Airlift()
{
}

bool Airlift::validate()
{
    if (this->dataPayload->sourceTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->targetTerritory->getOwningPlayer() == nullptr ||
        this->dataPayload->map == nullptr)
    {
        return false;
    }

    if (*this->dataPayload->sourceTerritory->getOwningPlayer() !=
            *this->dataPayload->targetTerritory->getOwningPlayer() ||
        *this->dataPayload->player !=
            *this->dataPayload->sourceTerritory->getOwningPlayer())
    {
        return false;
    }

    return true;
}

void Airlift::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Can not airlift from or to enemy territory."
                  << std::endl;
        return;
    }

    Territory sourceCopy = *this->dataPayload->sourceTerritory;
    sourceCopy.addArmies(-*this->dataPayload->numberOfArmies);
    this->dataPayload->map->updateTerritory(*this->dataPayload->sourceTerritory,
                                            sourceCopy);

    Territory targetCopy = *this->dataPayload->targetTerritory;
    targetCopy.addArmies(*this->dataPayload->numberOfArmies);
    this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory,
                                            targetCopy);

    this->setExecutedStatus(true);
}

Order *Airlift::clone() const
{
    return new Airlift(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Negotiate
//============================================================================================================================================================

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
    Order("Negotiate", "Negotiate with the opposition to reach an agreement",
          REMAINDER_PRIORITY)
{
}

Negotiate::~Negotiate()
{
}

bool Negotiate::validate()
{
    if (this->dataPayload->player == nullptr ||
        this->dataPayload->enemyPlayer == nullptr)
    {
        return false;
    }

    if (*this->dataPayload->player == *this->dataPayload->enemyPlayer)
    {
        return false;
    }

    return true;
}

void Negotiate::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid negotiation. Target player == player." << std::endl;
        return;
    }

    this->dataPayload->player->addToNegotiatorsList(this->dataPayload->enemyPlayer);
    this->dataPayload->enemyPlayer->addToNegotiatorsList(this->dataPayload->player);
    this->setExecutedStatus(true);
}

Order *Negotiate::clone() const
{
    return new Negotiate(*this);
}