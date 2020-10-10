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
        Player(const std::string& playerName,const std::vector<int>& territoriesAttack, const std::vector<int>& territoriesDefend, const std::vector<int>& cards, const std::vector<int>& orders);
        Player(const Player& player);
        Player();
        Player& operator= (const Player& player);
        ~Player();
        friend std::ostream& operator<<( std::ostream &output, const Player& player);
        std::vector<int>& toAttack();
        std::vector<int>& toDefend();
        std::vector<int>& getCards();
        std::vector<int>& getOrders();
        std::string& getPlayerName();
        void issueOrder();

};
#endif
