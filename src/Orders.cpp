#include "Orders.h"
#include <algorithm>
using std::vector;
using std::ostream;
using std::cout;
using std::string;

OrdersList::OrdersList(): orders(new vector<Order*>()){}

OrdersList::OrdersList(const OrdersList &ordersList): orders(new vector<Order*>(*ordersList.orders)){}

OrdersList& OrdersList::operator = (const OrdersList &ordersList){
    if(this == &ordersList){ 
        return *this; 
    }

    orders = new vector<Order*>(*ordersList.orders);
    return *this;
} 

ostream & operator << (ostream &out, const OrdersList &ordersList) 
{ 
    for (const Order* order : *ordersList.orders){
        cout << *order << "\n";
    }
    return out; 
} 


void OrdersList::addToList(Order& order){ 
    orders->push_back(order.clone());
}

void OrdersList::move(Order& order, int index){
    for (std::size_t i = 0; i < orders->size(); ++i){
        if ((*orders->at(i)->uniqueId) == *order.uniqueId){
            Order* temp = orders->at(i);
            orders->erase(std::next(orders->cbegin(), i));
            orders->insert(std::next(orders->cbegin(), index), temp);
            break;
        }
    }
}

void OrdersList::moveToFront(Order& order){
    this->move(order, 0);
}

void OrdersList::moveToEnd(Order& order){
    this->move(order, orders->size()-1);
}

void OrdersList::moveUp(Order& order){
    vector<Order*>::iterator it = find_if(orders->begin(), orders->end(), [&order](const Order* q){ return *(q->uniqueId) == **(&order.uniqueId);});

    if(it != orders->end()){
        int index = (it - orders->begin());
        if(index != 0){
            this->move(order, index-1);
        }
    }
}

void OrdersList::moveDown(Order& order){
    vector<Order*>::iterator it = find_if(orders->begin(), orders->end(), [&order](const Order* q){ return *(q->uniqueId) == **(&order.uniqueId);});

    if(it != orders->end()){
        int index = (it - orders->begin());
        if(static_cast<std::size_t>(index) != (orders->size()-1)){
            this->move(order, index+1);
        }
    }
}

void OrdersList::remove(Order& order){
    for (auto it = orders->cbegin(); it != orders->cend(); ++it){
        if((*(*it)->uniqueId) == *order.uniqueId){  
            orders->erase(it);
            break;
        }
    }
}

const vector<Order*>& OrdersList::getList(){ 
    return *orders; 
}

int Order::counter = 0;

Order::Order(const Order &order): uniqueId(new int(*order.uniqueId)),
                                  executed(new bool(*order.executed)),
                                  description(new std::string(*order.description)),
                                  effect(new std::string(*order.effect))
{}

Order& Order::operator = (const Order &order){
    if(this == &order){ 
        return *this; 
    }

    description = new string(*order.description);
    effect = new string(*order.effect);
    executed = new bool(*order.executed);
    uniqueId = new int(*order.uniqueId);

    return *this;
} 


Order::Order(const string description, const string effect): description(new string(description)), effect(new string(effect)){
    uniqueId = new int(counter++);
}

const string& Order::getDescription(){ 
    return *description; 
}

const string& Order::getEffect(){ 
    return *effect; 
}

void Order::setExecutedStatus(bool status){ *executed = status; }

const bool& Order::getExecutedStatus(){ return *executed; }

ostream & operator << (ostream &out, const Order &order) 
{ 
    out << *(order.description); 
    if(*(order.executed)){
         out << " -> Effect: " << *(order.effect); 
    };
    out << "\n"; 
    return out; 
} 

Deploy::Deploy(const Deploy &order): Order(order){}

Deploy& Deploy::operator = (const Deploy &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Deploy::Deploy():Order("Deploy", "Deploy troops to a territory"){}

void Deploy::validate(){}

void Deploy::execute(){ this->setExecutedStatus(true); } 

Order* Deploy::clone() const { return new Deploy(*this); }

Advance::Advance(const Advance &order): Order(order){}

Advance& Advance::operator = (const Advance &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Advance::Advance():Order("Advance", "Advance troops to a neighbouring territory"){}

void Advance::validate(){}

void Advance::execute(){ this->setExecutedStatus(true); }

Order* Advance::clone() const { return new Advance(*this); }

Bomb::Bomb(const Bomb &order): Order(order){}

Bomb& Bomb::operator = (const Bomb &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Bomb::Bomb():Order("Bomb", "Bomb a territory"){}

void Bomb::validate(){}

void Bomb::execute(){ this->setExecutedStatus(true); }

Order* Bomb::clone() const { return new Bomb(*this); }

Blockade::Blockade(const Blockade &order): Order(order){}

Blockade& Blockade::operator = (const Blockade &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Blockade::Blockade():Order("Blockade", "Seals a territory, Prevents people or goods from entering or leaving the territory"){}

void Blockade::validate(){}

void Blockade::execute(){ this->setExecutedStatus(true); }

Order* Blockade::clone() const { return new Blockade(*this); }

Airlift::Airlift(const Airlift &order): Order(order){}

Airlift& Airlift::operator = (const Airlift &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Airlift::Airlift():Order("Airlift", "Transport suplies or troops by air"){}

void Airlift::validate(){}

void Airlift::execute(){ this->setExecutedStatus(true); }

Order* Airlift::clone() const { return new Airlift(*this); }

Negotiate::Negotiate(const Negotiate &order): Order(order){}

Negotiate& Negotiate::operator = (const Negotiate &order){
    if (&order == this){
        return *this;
    }
    Order::operator= (order);
    return *this;
}

Negotiate::Negotiate():Order("Negotiate", "Negotiate with the opposition to reach an agreement"){}

void Negotiate::validate(){}

void Negotiate::execute(){ this->setExecutedStatus(true); }

Order* Negotiate::clone() const { return new Negotiate(*this); }