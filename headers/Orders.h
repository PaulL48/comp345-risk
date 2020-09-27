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

        //void delete();
    
    private:
        void move(Order& order, int index);
        vector<Order*> orders;
};

class Order{
    public:
        virtual void validate() = 0;
        virtual void execute() = 0;
};

class Deploy: public Order{
    public: 
        void validate();
        void execute();
};

class Advance: public Order{
    public: 
        void validate();
        void execute();
};

class Bomb: public Order{
    public: 
        void validate();
        void execute();
};

class Blockade: public Order{
    public: 
        void validate();
        void execute();
};

class Airlift: public Order{
    public: 
        void validate();
        void execute();
};

class Negotiate: public Order{
    public: 
        void validate();
        void execute();
};

#endif