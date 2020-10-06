#ifndef ORDERS_H
#define ORDERS_H
#include <Vector>
#include <iostream>

class Order;
class OrdersList{
    public:
        OrdersList();
        OrdersList(const OrdersList &order);
        OrdersList& operator = (const OrdersList &order); 
        ~OrdersList();
        friend std::ostream & operator << (std::ostream &out, const OrdersList &ordersList); 
        void addToList(const Order& order);
        void moveToFront(const Order& order);
        void moveToEnd(const Order& order);
        void moveUp(const Order& order);
        void moveDown(const Order& order);
        void remove(const Order& order);
        const std::vector<Order*>& getList();
    
    private:
        void move(const Order& order, int index);
        std::vector<Order*> *orders;
};

class Order{
    public:
        Order(const std::string& description, const std::string& effect);
        virtual ~Order();
        const std::string&  getDescription();
        const std::string& getEffect();
        const bool& getExecutedStatus();
        void setExecutedStatus(bool status);
        friend std::ostream & operator << (std::ostream &out, const Order &order); 
        virtual void validate() = 0;
        virtual void execute() = 0;
        virtual Order* clone() const = 0;
        int* uniqueId;

    protected:
        Order(const Order &order);
        Order& operator = (const Order &order); 
        bool* executed = new bool(false);
        std::string* description;
        std::string* effect;
        static int counter;

};

class Deploy: public Order{
    public: 
        Deploy();
        Deploy(const Deploy &order);
        virtual ~Deploy();
        Deploy& operator = (const Deploy &order); 
        void validate();
        void execute();
        virtual Order* clone() const;
};

class Advance: public Order{
    public: 
        Advance();
        Advance(const Advance &order);
        virtual ~Advance();
        Advance& operator = (const Advance &order);
        void validate();
        void execute();
        virtual Order* clone() const;
};

class Bomb: public Order{
    public: 
        Bomb();
        Bomb(const Bomb &order);
        virtual ~Bomb();
        Bomb& operator = (const Bomb &order);
        void validate();
        void execute();
        virtual Order* clone() const;
};

class Blockade: public Order{
    public: 
        Blockade();
        Blockade(const Blockade &order);
        virtual ~Blockade();
        Blockade& operator = (const Blockade &order);
        void validate();
        void execute();
        virtual Order* clone() const;
};

class Airlift: public Order{
    public: 
        Airlift();
        Airlift(const Airlift &order);
        virtual ~Airlift();
        Airlift& operator = (const Airlift &order);
        void validate();
        void execute();
        virtual Order* clone() const;
};

class Negotiate: public Order{
    public: 
        Negotiate();
        Negotiate(const Negotiate &order);
        virtual ~Negotiate();
        Negotiate& operator = (const Negotiate &order);
        void validate();
        void execute();
        virtual Order* clone() const;
};

#endif