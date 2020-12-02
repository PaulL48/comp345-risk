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

void OrdersList::clear()
{
    this->orders->clear();
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

const OrderDataPayload &Order::getDataPayload() const
{
    return *this->dataPayload;
}

ostream &operator<<(ostream &out, const Order &order)
{
    order.print(out);
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
    if (this->dataPayload->map == nullptr)
    {
        return false;
    }

    // Get up to date territory descritpions
    const Territory* target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    if (target == nullptr || this->dataPayload->player == nullptr)
    {
        return false;
    }

    return *target->getOwningPlayer() == *this->dataPayload->player;
}

void Deploy::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Target territory does not belong to player."
                  << std::endl;
        return;
    }

    // Get up to date territory descritpions
    const Territory* target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    Territory copy = *target;
    copy.addArmies(*this->dataPayload->numberOfArmies);
    *this->effect = std::to_string(*this->dataPayload->numberOfArmies) +
                " were deployed to " +
                target->getName();
    this->dataPayload->player->addArmies(-*this->dataPayload->numberOfArmies);
    this->dataPayload->map->updateTerritory(*target, copy);
    this->setExecutedStatus(true);
}

Order *Deploy::clone() const
{
    return new Deploy(*this);
}

std::ostream &Deploy::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << *this->dataPayload->numberOfArmies << " armies deploying to "
               << this->dataPayload->targetTerritory->getName();
    }

    return output;
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
    if (this->dataPayload->map == nullptr)
    {
        return false;
    }

    // Get up to date territory descritpions
    const Territory* source = this->dataPayload->map->getTerritory(*this->dataPayload->sourceTerritory);
    const Territory* target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    if (source->getOwningPlayer() == nullptr ||
        target->getOwningPlayer() == nullptr)
    {
        return false;
    }

    // No offensive advance on players in negotiation
    if (*target->getOwningPlayer() != *source->getOwningPlayer() &&
        this->dataPayload->player->isNegotiator(target->getOwningPlayer()))
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

    // Get up to date territory descritpions
    const Territory* source = this->dataPayload->map->getTerritory(*this->dataPayload->sourceTerritory);
    const Territory* target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    // Subtract territories
    Territory copy = *source;
    copy.addArmies(-*this->dataPayload->numberOfArmies);
    

    // Reinforcing territory
    if (source->getOwningPlayer() == target->getOwningPlayer())
    {
        Territory tcopy = *target;
        tcopy.addArmies(*this->dataPayload->numberOfArmies);
        this->dataPayload->map->updateTerritory(*target, tcopy);
        this->dataPayload->map->updateTerritory(*source, copy);
        return;
    }

    // Attacking territory
    std::default_random_engine generator(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<int> distribution(1, 100);
    auto killProbability = std::bind(distribution, generator);
    int attackingArmies = *this->dataPayload->numberOfArmies;
    int defendingArmies = target->getOccupyingArmies();

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
        Territory tcopy = *target;
        tcopy.setOwningPlayer(*this->dataPayload->player);
        tcopy.setOccupyingArmies(attackingArmies);
        *this->effect = target->getName() + " was conquered by " +
                        this->dataPayload->player->getPlayerName() + ", with " +
                        std::to_string(attackingArmies) + " armies now occupying it";
        this->dataPayload->map->updateTerritory(*target, tcopy);
        this->dataPayload->map->updateTerritory(*source, copy);
    }
    else
    {
        Territory tcopy = *target;
        tcopy.setOccupyingArmies(defendingArmies);
        *this->effect = target->getName() + " resisted the attack from " +
                        source->getName() + ", with " +
                        std::to_string(defendingArmies) + " armies remaining";
        this->dataPayload->map->updateTerritory(*target, tcopy);
        this->dataPayload->map->updateTerritory(*source, copy);
    }
    this->setExecutedStatus(true);
}

Order *Advance::clone() const
{
    return new Advance(*this);
}

std::ostream &Advance::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << *this->dataPayload->numberOfArmies << " armies are moving from "
               << this->dataPayload->sourceTerritory->getName() << " to "
               << this->dataPayload->targetTerritory->getName();
    }
    return output;
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
    if (this->dataPayload->map == nullptr)
    {
        return false;
    }

    // Get up to date territory descritpions
    const Territory *target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    if (target->getOwningPlayer() == nullptr)
    {
        return false;
    }

    if (this->dataPayload->player->isNegotiator(target->getOwningPlayer()))
    {
        return false;
    }

    if (*target->getOwningPlayer() == *this->dataPayload->player)
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

    // Get up to date territory descritpions
    const Territory *target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    Territory copy = *target;
    copy.setOccupyingArmies(copy.getOccupyingArmies() / 2);
    *this->effect =
        this->dataPayload->player->getPlayerName() + " has dropped a bomb on " +
        target->getName() + ", leaving it with " +
        std::to_string(copy.getOccupyingArmies()) + " armies remaining";
    this->dataPayload->map->updateTerritory(*target, copy);
    this->setExecutedStatus(true);
}

Order *Bomb::clone() const
{
    return new Bomb(*this);
}

std::ostream &Bomb::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << this->dataPayload->player->getPlayerName()
               << " is dropping a bomb on "
               << this->dataPayload->targetTerritory->getName();
    }
    return output;
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
    if (this->dataPayload->map == nullptr)
    {
        return false;
    }
    
    // Get up to date territory descritpions
    const Territory *target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    if (target->getOwningPlayer() == nullptr)
    {
        return false;
    }

    return *target->getOwningPlayer() == *this->dataPayload->player;
}

void Blockade::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid order. Territory does not belong to player." << std::endl;
        return;
    }

    // Get up to date territory descritpions
    const Territory *target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    Territory copy = *target;
    copy.setOccupyingArmies(copy.getOccupyingArmies() * 2);
    copy.unsetOwningPlayer();
    *this->effect =
        target->getName() + " has been blockaded. " +
        std::to_string(copy.getOccupyingArmies()) + " neutral forces defend it";
    this->dataPayload->map->updateTerritory(*target, copy);
    this->setExecutedStatus(true);
}

Order *Blockade::clone() const
{
    return new Blockade(*this);
}

std::ostream &Blockade::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << this->dataPayload->player->getPlayerName()
               << " is creating a blockade in "
               << this->dataPayload->targetTerritory->getName();
    }
    return output;
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
    if (this->dataPayload->map == nullptr)
    {
        return false;
    }

    // Get up to date territory descritpions
    const Territory *source = this->dataPayload->map->getTerritory(*this->dataPayload->sourceTerritory);
    const Territory *target = this->dataPayload->map->getTerritory(*this->dataPayload->targetTerritory);

    if (source->getOwningPlayer() == nullptr ||
        target->getOwningPlayer() == nullptr)
    {
        return false;
    }

    if (*source->getOwningPlayer() != *target->getOwningPlayer() ||
        *this->dataPayload->player != *source->getOwningPlayer())
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

    Territory targetCopy = *this->dataPayload->targetTerritory;
    targetCopy.addArmies(*this->dataPayload->numberOfArmies);
    *this->effect = std::to_string(*this->dataPayload->numberOfArmies) +
                    " armies were airlifted to " +
                    this->dataPayload->targetTerritory->getName() + " from " +
                    this->dataPayload->sourceTerritory->getName();
    this->dataPayload->map->updateTerritory(*this->dataPayload->targetTerritory,
                                            targetCopy);
    this->dataPayload->map->updateTerritory(*this->dataPayload->sourceTerritory,
                                            sourceCopy);
    this->setExecutedStatus(true);
}

Order *Airlift::clone() const
{
    return new Airlift(*this);
}

std::ostream &Airlift::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << *this->dataPayload->numberOfArmies << " armies are airlifting from "
               << this->dataPayload->sourceTerritory->getName() << " to "
               << this->dataPayload->targetTerritory->getName();
    }
    return output;
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
    *this->effect = this->dataPayload->player->getPlayerName() +
                    " has entered negotiations with " +
                    this->dataPayload->enemyPlayer->getPlayerName() +
                    ". Battle has stopped for now";
    this->setExecutedStatus(true);
}

Order *Negotiate::clone() const
{
    return new Negotiate(*this);
}

std::ostream &Negotiate::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << this->dataPayload->player->getPlayerName()
               << " is entering negotiations with "
               << this->dataPayload->enemyPlayer->getPlayerName();
    }
    return output;
}

Reinforcement::Reinforcement() :
    Order("Reinforcement", "Gain extra reinforcements to deploy this turn", REMAINDER_PRIORITY)
{
}

Reinforcement::~Reinforcement()
{
}

bool Reinforcement::validate()
{
    if (this->dataPayload->map == nullptr || this->dataPayload->player == nullptr)
    {
        return false;
    }

    return true;
}

void Reinforcement::execute()
{
    if (!this->validate())
    {
        std::cout << "Invalid reinforcement" << std::endl;
        return;
    }

    this->dataPayload->player->addArmies(*this->dataPayload->numberOfArmies);
    *this->effect = this->dataPayload->player->getPlayerName() +
                    " has gained " + std::to_string(*this->dataPayload->numberOfArmies) +
                    " extra reinforcements";
    this->setExecutedStatus(true);
}

Order *Reinforcement::clone() const
{
    return new Reinforcement(*this);
}

std::ostream &Reinforcement::print(std::ostream &output) const
{
    if (*this->executed)
    {
        output << *this->effect << std::endl;
    }
    else
    {
        output << this->dataPayload->player->getPlayerName()
               << " is receiving " << *this->dataPayload->numberOfArmies << " extra reinforcements"; 
    }
    return output;
}

Deploy OrderBuilder::buildDeployOrder(Map *map, Player *player, const Territory &target, int numberOfArmies)
{
    Deploy order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    order.getMutableDataPayload().targetTerritory = new Territory(target);
    *order.getMutableDataPayload().numberOfArmies = numberOfArmies;
    return order;
}

Advance OrderBuilder::buildAdvanceOrder(Map *map, Player *player, const Territory &source, const Territory &target, int numberOfArmies)
{
    Advance order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    order.getMutableDataPayload().sourceTerritory = new Territory(source);
    order.getMutableDataPayload().targetTerritory = new Territory(target);
    *order.getMutableDataPayload().numberOfArmies = numberOfArmies;
    return order;
}

Bomb OrderBuilder::buildBombOrder(Map *map, Player *player, const Territory &target)
{
    Bomb order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    order.getMutableDataPayload().targetTerritory = new Territory(target);
    return order;
}

Blockade OrderBuilder::buildBlockadeOrder(Map *map, Player *player, const Territory &target)
{
    Blockade order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    order.getMutableDataPayload().targetTerritory = new Territory(target);
    return order;
}

Airlift OrderBuilder::buildAirlift(Map *map, Player *player, const Territory &source, const Territory &target, int numberOfArmies)
{
    Airlift order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    order.getMutableDataPayload().sourceTerritory = new Territory(source);
    order.getMutableDataPayload().targetTerritory = new Territory(target);
    *order.getMutableDataPayload().numberOfArmies = numberOfArmies;
    return order;
}

Negotiate OrderBuilder::buildNegotiate(Map *map, Player *initiatingPlayer, Player *targetPlayer)
{
    Negotiate order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = initiatingPlayer;
    order.getMutableDataPayload().enemyPlayer = targetPlayer;
    return order;
}

Reinforcement OrderBuilder::buildReinforcement(Map *map, Player *player)
{
    Reinforcement order;
    order.getMutableDataPayload().map = map;
    order.getMutableDataPayload().player = player;
    *order.getMutableDataPayload().numberOfArmies = 10;
    return order;
}

