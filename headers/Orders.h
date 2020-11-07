#ifndef ORDERS_H
#define ORDERS_H
#include <iostream>
#include <vector>
#include "Player.h"

class Territory;
class Player;
template <typename T>
void polymorphicDeepCopy(std::vector<T *> &dest, const std::vector<T *> &source)
{
    // Free previous elements
    for (T *element : dest)
    {
        delete element;
    }

    dest.resize(source.size());

    // Clone polymorphic elements
    for (std::size_t i = 0; i < dest.size(); ++i)
    {
        dest.at(i) = source.at(i)->clone();
    }
}

template <typename T>
std::vector<T *> *clone(const std::vector<T *> &vector)
{
    std::vector<T *> *result = new std::vector<T *>(vector.size());
    for (std::size_t i = 0; i < result->size(); ++i)
    {
        result->at(i) = vector.at(i)->clone();
    }
    return result;
}

class Order;
class OrdersList
{
public:
    OrdersList();                                   // constructor
    OrdersList(const OrdersList &order);            // copy constructor
    OrdersList &operator=(const OrdersList &order); // copy assignment operator
    ~OrdersList();                                  // destructor
    friend std::ostream &
    operator<<(std::ostream &out,
               const OrdersList &ordersList); // stream insertion operator
    void addToList(const Order &order);       // adds an order to the end of a list
    void moveToFront(const Order &order);     // moves an order to the front of the list
    void moveToEnd(const Order &order);       // moves an order to the end of the list
    void moveUp(const Order &order);          // moves an order up by one position
    void moveDown(const Order &order);        // moves an order down by one position
    void remove(const Order &order);          // removes an order from the list
    const std::vector<Order *> &getList(); // returns orders vector by const reference

private:
    void move(const Order &order,
              int index);         // private move method used to by public move methods
    std::vector<Order *> *orders; // vector pointer to hold Order pointers
};

class Order
{
public:
    Order(const std::string &description,
          const std::string &effect); // constructor
    virtual ~Order();                 // destructor
    const std::string &
    getDescription();                // returns description string by const reference
    const std::string &getEffect();  // returns effect string by const reference
    const bool &getExecutedStatus(); // returns executed status bool by const reference
    void setExecutedStatus(bool status); // sets executed status
    friend std::ostream &operator<<(std::ostream &out,
                                    const Order &order); // stream insertion operator
    virtual Order *clone() const = 0; // clones an Order object and returns Order
                                      // pointer, virtual method
    int getUniqueId() const;

protected:
    Order(const Order &order);            // copy constructor
    Order &operator=(const Order &order); // copy assignment operator
    virtual bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const territoryA, const Territory* const territoryB) = 0;
    virtual void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer) = 0;  
    int *uniqueId;
    bool *executed = new bool(false); // initialized to false
    std::string *description;
    std::string *effect;
    static int counter;
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(const Deploy &order);
    virtual ~Deploy();
    Deploy &operator=(const Deploy &order);
    void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory); 
    virtual Order *clone() const;
private:
    bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
    void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);
};

class Advance : public Order
{
public:
    Advance();
    Advance(const Advance &order);
    virtual ~Advance();
    Advance &operator=(const Advance &order);
    void execute(Player* player, int numberOfArmies, Territory* targetTerritory, Territory* sourceTerritory);
    virtual Order *clone() const;
private:
    bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
    void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(const Bomb &order);
    virtual ~Bomb();
    Bomb &operator=(const Bomb &order);
    void execute(Player* player, Territory* targetTerritory); 
    virtual Order *clone() const;
private:
    bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
    void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(const Blockade &order);
    virtual ~Blockade();
    Blockade &operator=(const Blockade &order);
    void execute(Player* player, Territory* targetTerritory);
    virtual Order *clone() const;
private:
        bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
        void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);
};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(const Airlift &order);
    virtual ~Airlift();
    Airlift &operator=(const Airlift &order);
    void execute(Player* player, int numberOfArmies, Territory* targetTerritory, Territory* sourceTerritory); 
    virtual Order *clone() const;
private:
        bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
        void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(const Negotiate &order);
    virtual ~Negotiate();
    Negotiate &operator=(const Negotiate &order);
    void execute(Player* player, Player* enemyPlayer); 
    virtual Order *clone() const;
private:
        bool validate(const Player* const player, const Player* const enemyPlayer, const Territory* const targetTerritory, const Territory* const sourceTerritory);      // validates an order, virtual method
        void execute(Player* const player, int numberOfArmies, Territory* const targetTerritory, Territory* const sourceTerritory, Player* const enemyPlayer);

};

#endif
