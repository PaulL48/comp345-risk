#include "Orders.h"
#include <algorithm>
using namespace std;

void OrdersList::addToList(Order& order){
    orders.push_back(&order);
}

void OrdersList::move(Order& order, int index){
    vector<Order*>::iterator it;
    int i;

    for(it = orders.begin(), i = 0; it != orders.end(); ++it, ++i){
        if(*it == &order){  
            Order *orderPointer = *it;
            orders.erase(it);
            orders.insert(next(orders.begin(), index), orderPointer);
        }
    }
}

void OrdersList::moveToFront(Order& order){
    this->move(order, 0);
}

void OrdersList::moveToEnd(Order& order){
    this->move(order, orders.size()-1);
}

void OrdersList::moveUp(Order& order){
    vector<Order*>::iterator it = find_if(orders.begin(), orders.end(), [&order](const Order* q){ return q == &order;});

    if(*it == &order){
        int index = (it - orders.begin());
        if(index != 0){
            this->move(order, index-1);
        }
    }
}

void OrdersList::moveDown(Order& order){
    vector<Order*>::iterator it = find_if(orders.begin(), orders.end(), [&order](const Order* q){ return q == &order;});

    if(*it == &order){
        int index = (it - orders.begin());
        if((unsigned long long)index != (orders.size()-1)){
            this->move(order, index+1);
        }
    }
}

void OrdersList::remove(Order& order){
    vector<Order*>::iterator it;

    for(it = orders.begin(); it != orders.end(); ++it){
        if(*it == &order){  
            orders.erase(it);
            break;
        }
    }
}

Order::Order(const Order &order){
    description = new string(*order.description);
    effect = new string(*order.effect);
    executed = new bool(*order.executed);
}

Order::Order(string description, string effect): description(new string(description)), effect(new string(effect)){}

string Order::getDescription(){ return *description; }

string Order::getEffect(){ return *effect; }

void Order::setExecutedStatus(bool status){ executed = new bool(status); }

bool Order::getExecutedStatus(){ return executed; }

ostream & operator << (ostream &out, const Order &order) 
{ 
    out << *(order.description); 
    if(*(order.executed)){ out << " -> Effect: " << *(order.effect); };
    out << "\n"; 
    return out; 
} 

Deploy::Deploy(const Deploy &order): Order(order){}

Deploy::Deploy():Order("Deploy", "Deploy troops to a territory"){}

void Deploy::validate(){}

void Deploy::execute(){ this->setExecutedStatus(true); } 

Advance::Advance(const Advance &order): Order(order){}

Advance::Advance():Order("Advance", "Advance troops to a neighbouring territory"){}

void Advance::validate(){}

void Advance::execute(){ this->setExecutedStatus(true); }

Bomb::Bomb(const Bomb &order): Order(order){}

Bomb::Bomb():Order("Bomb", "Bomb a territory"){}

void Bomb::validate(){}

void Bomb::execute(){ this->setExecutedStatus(true); }

Blockade::Blockade(const Blockade &order): Order(order){}

Blockade::Blockade():Order("Blockade", "Seals a territory, Prevents people or goods from entering or leaving the territory"){}

void Blockade::validate(){}

void Blockade::execute(){ this->setExecutedStatus(true); }

Airlift::Airlift(const Airlift &order): Order(order){}

Airlift::Airlift():Order("Airlift", "Transport suplies or troops by air"){}

void Airlift::validate(){}

void Airlift::execute(){ this->setExecutedStatus(true); }

Negotiate::Negotiate(const Negotiate &order): Order(order){}

Negotiate::Negotiate():Order("Negotiate", "Negotiate with the opposition to reach an agreement"){}

void Negotiate::validate(){}

void Negotiate::execute(){ this->setExecutedStatus(true); }