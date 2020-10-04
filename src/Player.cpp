#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * This is the main constructor for the Player Class.
 * */
Player::Player(std::string* playerName,std::vector<int>* territoriesAttack, std::vector<int>* territoriesDefend, std::vector<int>* cards, std::vector<int>* orders):
    playerName(playerName), territoriesAttack(territoriesAttack), territoriesDefend(territoriesDefend), cards(cards), orders(orders){}


/**
 * This is the issueOrder method. 
 * This method creates an Order and adds it to the players orders vector.
 * */
void Player::issueOrder(){
    /**
     * Add the creation of the order - Ask the teacher on what the creation does exactly and how do we determine if it is a attack or defend order
     * */
    Player::orders->push_back(5);
}
/**
 * This is the copy constructor that takes in a Player object and creates a new Player
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
 * This is the stream insertion operator
 * */
std::ostream &operator<<(std::ostream &output, const Player &p){
    output 
        <<"{  Player Name: " << p.playerName <<
        ", Orders : " << p.orders << ", Territories Attack: " << p.territoriesAttack 
        << ",  Territories Defend: " << p.territoriesDefend << ",  Cards: " << p.cards ;
    return output;
}