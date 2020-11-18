#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <iostream>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"


class Player{
    private:
        std::string* playerName;
        std::vector<Territory>* territoriesAttack;
        std::vector<Territory>* territoriesDefend;
        std::vector<int>* playerOrder; 
        int* numArmies;
        Hand* cards;
        OrdersList* orders;
    public:
        Player(const std::string& playerName,const std::vector<Territory>& territoriesAttack, const std::vector<Territory>& 
        territoriesDefend, const Hand& cards, const OrdersList& orders, const int& numArmies,const std::vector<int>& playerOrder);
        Player(const Player& player);
        Player();
        Player& operator= (const Player& player);
        bool operator==(const Player& player) const;
        ~Player();
        friend std::ostream& operator<<( std::ostream &output, const Player& player);
        std::vector<Territory>& toAttack();
        std::vector<Territory>& toDefend();
        std::vector<int>& getPlayerOrder();
        Hand& getCards();
        OrdersList& getOrders();
        std::string& getPlayerName();
        void issueOrder();
        int& getNumArmies();

};
#endif
