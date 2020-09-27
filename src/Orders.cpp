#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;

void OrdersList::addToList(Order& order){
    orders.push_back(&order);
}

void OrdersList::move(Order& order, int index){
    vector<Order*>::iterator it;
for(it = orders.begin(); it != orders.end(); ++it){
       cout << *it << "\n";
    }
    int i;
    for(it = orders.begin(), i = 0; it != orders.end(); ++it, ++i){
        if(*it == &order){  
            Order *orderPointer = *it;
            orders.erase(it);
            orders.insert(next(orders.begin(), index), orderPointer);
        }
    }
    for(it = orders.begin(); it != orders.end(); ++it){
       cout << *it << "\n";
    }
}

void OrdersList::moveToFront(Order& order){
    this->move(order, 0);
}

void OrdersList::moveToEnd(Order& order){
    this->move(order, orders.size()-1);
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