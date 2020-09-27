#include "Orders.h"
#include <list>
#include <iostream>
using namespace std;

void OrdersList::addToList(Order& order){
    orders.push_back(&order);
}

void OrdersList::move(Order& order, int index){
    list<Order*>::iterator it;
  
    for(it = orders.begin(); it != orders.end(); ++it){
        if(*it == &order){  
            orders.splice(next(orders.begin(), index), orders, it);
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