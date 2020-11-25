#ifndef ORDERS_H
#define ORDERS_H

#include "Player.h"
#include <iostream>
#include <vector>

constexpr int DEPLOY_PRIORITY = 1;
constexpr int AIRLIFT_PRIORITY = 2;
constexpr int BLOCKADE_PRIORITY = 3;
constexpr int REMAINDER_PRIORITY = 4;

class Territory;
class Player;
class Map;

// Suspect
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

struct OrderDataPayload
{
    OrderDataPayload();
    OrderDataPayload(const OrderDataPayload &odp);
    ~OrderDataPayload();

    OrderDataPayload &operator=(const OrderDataPayload &odp);

    Player *player;
    Player *enemyPlayer;
    int *numberOfArmies; // Owning pointer
    Territory *sourceTerritory;
    Territory *targetTerritory;
    Map *map;
};

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
    const std::vector<Order *> &getList();    // returns orders vector

private:
    void move(const Order &order,
              int index);         // private move method used to by public move methods
    std::vector<Order *> *orders; // vector pointer to hold Order pointers
};

class Order
{
public:
    Order(const std::string &description, const std::string &effect,
          int executionPriority);         // constructor
    virtual ~Order();                     // destructor
    Order(const Order &order);            // copy constructor
    Order &operator=(const Order &order); // copy assignment operator
    const std::string &getDescription();  // returns description string
    const std::string &getEffect();       // returns effect string
    const bool &getExecutedStatus();      // returns executed status bool
    void setExecutedStatus(bool status);  // sets executed status
    friend std::ostream &operator<<(std::ostream &out,
                                    const Order &order); // stream insertion operator
    virtual Order *clone() const = 0; // clones an Order object and returns Order
                                      // pointer, virtual method
    int getUniqueId() const;
    int getExecutionPriority() const;

    OrderDataPayload &getMutableDataPayload();

    virtual void execute() = 0;
    virtual bool validate() = 0;

protected:
    virtual std::ostream &print(std::ostream &output) const = 0;

    int *uniqueId;
    bool *executed;
    std::string *description;
    std::string *effect;
    static int counter;
    OrderDataPayload *dataPayload;
    int *executionPriority;
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(const Deploy &order);
    virtual ~Deploy();
    Deploy &operator=(const Deploy &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

class Advance : public Order
{
public:
    Advance();
    Advance(const Advance &order);
    virtual ~Advance();
    Advance &operator=(const Advance &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(const Bomb &order);
    virtual ~Bomb();
    Bomb &operator=(const Bomb &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(const Blockade &order);
    virtual ~Blockade();
    Blockade &operator=(const Blockade &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(const Airlift &order);
    virtual ~Airlift();
    Airlift &operator=(const Airlift &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(const Negotiate &order);
    virtual ~Negotiate();
    Negotiate &operator=(const Negotiate &order);
    virtual void execute();
    virtual bool validate();
    virtual Order *clone() const;

protected:
    virtual std::ostream &print(std::ostream &output) const;
};

#endif
