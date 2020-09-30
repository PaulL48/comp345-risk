#ifndef ORDERS_H
#define ORDERS_H
#include <Vector>
#include <iostream>
using namespace std;

class Order;
class OrdersList{
    public:
        void addToList(Order& order);
        void moveToFront(Order& order);
        void moveToEnd(Order& order);
        void moveUp(Order& order);
        void moveDown(Order& order);
        void remove(Order& order);
        vector<Order*> getList();
    
    private:
        void move(Order& order, int index);
        vector<Order*> orders;
};

class Order{
    public:
        Order(string description, string effect);
        string getDescription();
        string getEffect();
        bool getExecutedStatus();
        void setExecutedStatus(bool status);
        friend ostream & operator << (ostream &out, const Order &order); 
        virtual void validate() = 0;
        virtual void execute() = 0;
    protected:
        Order(const Order &order);
        Order& operator = (const Order &order); 
        bool* executed = new bool(false);
        string* description;
        string* effect;
};

class Deploy: public Order{
    public: 
        Deploy();
        Deploy(const Deploy &order);
        void validate();
        void execute();
};

class Advance: public Order{
    public: 
        Advance();
        Advance(const Advance &order);
        void validate();
        void execute();
};

class Bomb: public Order{
    public: 
        Bomb();
        Bomb(const Bomb &order);
        void validate();
        void execute();
};

class Blockade: public Order{
    public: 
        Blockade();
        Blockade(const Blockade &order);
        void validate();
        void execute();
};

class Airlift: public Order{
    public: 
        Airlift();
        Airlift(const Airlift &order);
        void validate();
        void execute();
};

class Negotiate: public Order{
    public: 
        Negotiate();
        Negotiate(const Negotiate &order);
        void validate();
        void execute();
};

#endif