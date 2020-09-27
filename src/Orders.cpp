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

void Deploy::validate(){}

void Deploy::execute(){}

void Advance::validate(){}

void Advance::execute(){}

void Bomb::validate(){}

void Bomb::execute(){}

void Airlift::validate(){}

void Airlift::execute(){}

void Negotiate::validate(){}

void Negotiate::execute(){}