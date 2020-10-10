#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * This is the main constructor for the Player Class.
 * */
Player::Player(const std::string& playerName,const std::vector<int>& territoriesAttack, const std::vector<int>& territoriesDefend, const std::vector<int>& cards, const std::vector<int>& orders):
    playerName(new std::string(playerName)),territoriesAttack( new std::vector<int>(territoriesAttack)), territoriesDefend(new std::vector<int>(territoriesDefend)), cards(new std::vector<int>(cards)), orders(new std::vector<int>(orders)){}


Player::Player():playerName(new std::string("")), territoriesAttack(new std::vector<int>), territoriesDefend(new std::vector<int>), cards(new std::vector<int>), orders(new std::vector<int>){}
/**
 * This is the issueOrder method.
 * This method creates an Order and adds it to the players orders vector.
 * */
void Player::issueOrder(){
    /**
     * Add the creation of the order - Ask the teacher on what the creation does exactly and how do we determine if it is a attack or defend order
     * */
    orders->push_back(5);
}

Player::~Player(){ 
    delete playerName;
    delete territoriesAttack;
    delete territoriesDefend;
    delete cards;
    delete orders;
}

/**
 * This is the copy constructor that takes in a Player object and creates a new Player
 * */
Player::Player(const Player& p){
    playerName = new std::string(*p.playerName);
    territoriesAttack = new std::vector<int>(*p.territoriesAttack);
    territoriesDefend = new std::vector<int>(*p.territoriesDefend);
    cards =new std::vector<int>(*p.cards);
    orders =new std::vector<int>(*p.orders);
}
/**
 * This is the assignment operator for the Player object
 *
 * */
Player& Player::operator= (const Player& player){
    if (this == &player)
        return *this;

    *this->playerName = *player.playerName;
    *this->territoriesAttack = *player.territoriesAttack;
    *this->territoriesDefend = *player.territoriesDefend;
    *this->cards= *player.cards;
    *this->orders= *player.orders;
    return *this;
}

std::vector<int>& Player::toAttack(){
    return *territoriesAttack;
}
std::vector<int>& Player::toDefend(){
    return *territoriesDefend;
}
std::vector<int>& Player::getCards(){
    return *cards;
}

std::vector<int>& Player::getOrders(){
    return *orders;
}

std::string& Player::getPlayerName(){
    return *playerName;
}
/**
 * This is the stream insertion operator
 * */
std::ostream &operator<<(std::ostream &output, const Player &p){
    output <<"( Player Name: " << *p.playerName << ", Orders : ";
      for (const auto& order : *p.orders){
        output<< order << ",";
    }
    output<<"Territories Attack: ";
      for (const auto& territory : *p.territoriesAttack){
        output<< territory << ",";
    }
    output<<"Territories Defend: ";
    for (const auto& territory : *p.territoriesDefend){
        output<< territory << ",";
    }
    output<<"Cards : ";
    for (const auto& card : *p.cards){
        output<< card << ",";
    }
    output<<")";
    return output;
}