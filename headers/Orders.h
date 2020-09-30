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
    
    private:
        void move(Order& order, int index);
        vector<Order*> orders;
};

class Order{
    public:
        Order(string description, string effect);
        string getDescription();
        string getEffect();
        virtual void validate() = 0;
        virtual void execute() = 0;
    protected:
        string description;
        string effect;
};

class Deploy: public Order{
    public: 
        Deploy();
        void validate();
        void execute();
};

class Advance: public Order{
    public: 
        Advance();
        void validate();
        void execute();
};

class Bomb: public Order{
    public: 
        Bomb();
        void validate();
        void execute();
};

class Blockade: public Order{
    public: 
        Blockade();
        void validate();
        void execute();
};

class Airlift: public Order{
    public: 
        Airlift();
        void validate();
        void execute();
};

class Negotiate: public Order{
    public: 
        Negotiate();
        void validate();
        void execute();
};

#endif