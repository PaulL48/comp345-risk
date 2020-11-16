#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <iostream>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

class Hand;
class OrdersList;
class Player{
    private:
        std::string* playerName;
        std::vector<Territory>* territoriesAttack;
        std::vector<Territory>* territoriesDefend;
        Hand* cards;
        OrdersList* orders;
        std::vector<Player*>* negotiators; // the negotiate will set this value to true when a valid negotiate order is executed for territories involved in the negotiation 
    
    public:
        Player(const std::string& playerName,const std::vector<Territory>& territoriesAttack, const std::vector<Territory>& territoriesDefend, const Hand& cards, const OrdersList& orders);
        Player(const Player& player);
        Player();
        Player& operator= (const Player& player);
        ~Player();
        friend std::ostream& operator<<( std::ostream &output, const Player& player);
        std::vector<Territory>& toAttack();
        std::vector<Territory>& toDefend();
        Hand& getCards();
        OrdersList& getOrders();
        std::string& getPlayerName();
        void issueOrder();
        void addToNegotiatorsList(Player* player) const;
        bool isNegotiator(const Player* player) const;
};
#endif
