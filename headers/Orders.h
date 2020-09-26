#ifndef ORDERS_H
#define ORDERS_H
#include <list>
using namespace std;

class OrdersList{
    public:
        void move();
        //void delete();
    
    private:
        list<Order> orders;
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