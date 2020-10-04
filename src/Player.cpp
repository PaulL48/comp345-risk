#include "Player.h"
#include <string>
#include <list>
#include <iostream>

/**
 * 
 * */
Player::Player(std::string* playerName,std::vector<int>* territoriesAttack, std::vector<int>* territoriesDefend, std::vector<int>* cards, std::vector<int>* orders):
    playerName(playerName), territoriesAttack(territoriesAttack), territoriesDefend(territoriesDefend), cards(cards), orders(orders){}


/**
 * 
 * */
void Player::issueOrder(){
    /**
     * Add the creation of the order - Ask the teacher on what the creation does exactly and how do we determine if it is a attack or defend order
     * */
    Player::orders->push_back(5);
}
/**
 * 
 * */
Player::Player(const Player& p){
    playerName = p.playerName;
    territoriesAttack = p.territoriesAttack;
    territoriesDefend = p.territoriesDefend;
    cards = p.cards;
    orders = p.orders;
}
/**
 * This is the assignment operator for the Player object 
 * 
 * */
Player& Player::operator= (const Player& player){
    if (this == &player)
        return *this;
    
    *playerName = *player.playerName;
    *territoriesAttack = *player.territoriesAttack;
    *territoriesDefend = *player.territoriesDefend;
    *cards= *player.cards;
    *orders= *player.orders;
    return *this;
}
/**
 * 
 * */
std::ostream &operator<<(std::ostream &output, const Player &p){
    output 
        <<"{  Player Name: " << p.playerName <<
        ", Orders : " << p.orders << ", Territories Attack: " << p.territoriesAttack 
        << ",  Territories Defend: " << p.territoriesDefend << ",  Cards: " << p.cards ;
    return output;
}