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

Order::Order(string description, string effect): description(description), effect(effect){}

string Order::getDescription(){ return description; }

string Order::getEffect(){ return effect; }

void Order::setExecutedStatus(bool status){ executed = status; }

bool Order::getExecutedStatus(){ return executed; }

Deploy::Deploy():Order("Deploy army", "Deploy troops to a territory"){}

void Deploy::validate(){}

void Deploy::execute(){ this->setExecutedStatus(true); } 

Advance::Advance():Order("Advance", "Advance troops to a neighbouring territory"){}

void Advance::validate(){}

void Advance::execute(){ this->setExecutedStatus(true); }

Bomb::Bomb():Order("Bomb", "Bomb a territory"){}

void Bomb::validate(){}

void Bomb::execute(){ this->setExecutedStatus(true); }

Airlift::Airlift():Order("Airlift", "Transport suplies or troops by air"){}

void Airlift::validate(){}

void Airlift::execute(){ this->setExecutedStatus(true); }

Negotiate::Negotiate():Order("Negotiate", "Negotiate with the opposition to reach an agreement"){}

void Negotiate::validate(){}

void Negotiate::execute(){ this->setExecutedStatus(true); }