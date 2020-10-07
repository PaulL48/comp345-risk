#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <iostream>

class Player{
    private:
        std::string* playerName;
        std::vector<int>* territoriesAttack;
        std::vector<int>* territoriesDefend;
        std::vector<int>* cards;
        std::vector<int>* orders;
    public:
        Player(std::string* playerName,std::vector<int>* territoriesAttack, std::vector<int>* territoriesDefend, std::vector<int>* cards, std::vector<int>* orders);
        Player(const Player& player);
        Player& operator= (const Player& player);
        ~Player();
        friend std::ostream& operator<<( std::ostream &output, const Player& player);
        std::vector<int>* toAttack(){ return territoriesAttack;}
        std::vector<int>* toDefend(){ return territoriesDefend;}
        std::vector<int>* getCards(){ return cards;}
        std::vector<int>* getOrders(){return orders;}
        std::string* getPlayerName(){return playerName;}
        void issueOrder();

};
#endif
