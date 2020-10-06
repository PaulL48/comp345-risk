#include  "Player.h"
#include <iostream>
#include <vector> 

int testGetPlayerName(Player player, std::string* playerName){
    if(player.getPlayerName()->compare(*playerName) !=0 ){
        return 1;
    }
    else 
        return 0;
}
int testGetAttackTerriotories(Player player, std::vector<int>* attackTerritories){
    if(player.toAttack() == attackTerritories)
        return 0;
    else 
        return 1;
}
int testGetAttackDefendTerritories(Player player, std::vector<int>* defendTerritories){
    if(player.toDefend() == defendTerritories)
        return 0;
    else 
        return 1;
}
int testGetCards(Player player, std::vector<int>* cards){
    if(player.getCards() == cards)
        return 0;
    else 
        return 1;   
}
int testGetOrders(Player player, std::vector<int>* orders){
    if(player.getOrders() == orders)
        return 0; 
    else 
        return 1;
}

int main(){
    std::cout<<"IM HERE";
    std::vector<int>* initialAttackTerritories {};
    initialAttackTerritories->push_back(20);
    initialAttackTerritories->push_back(100);
    initialAttackTerritories->push_back(50);
    initialAttackTerritories->push_back(10);
    std::vector<int>* initialDefendTerritories {};
    initialDefendTerritories->push_back(5);
    initialDefendTerritories->push_back(25);
    initialDefendTerritories->push_back(30);
    initialDefendTerritories->push_back(5);

    std::string* playerName = new std::string("Sammy");

    std::vector<int>* cards {};
    cards->push_back(1);
    cards->push_back(2);
    cards->push_back(3);
    cards->push_back(4);

    std::vector<int>* orders {};
    orders->push_back(5);
    orders->push_back(6);
    orders->push_back(7);
    orders->push_back(8);

    Player player = Player(playerName, initialAttackTerritories,initialDefendTerritories,cards,orders);

    if(testGetPlayerName(player,playerName) == 0)
        std::cout << "The GetPlayerName has been successful ";
    else
        std::cout<< "The GetPlayerName has not been successful ";
    
    if(testGetAttackTerriotories(player, initialAttackTerritories) == 0)
        std::cout<< "The toAttack has been successful";
    else 
        std::cout<< "The toAttack has not been successful";
    
    if(testGetAttackDefendTerritories(player,initialDefendTerritories) == 0)
        std::cout<<  "The toDefend has been successful";
    else 
        std::cout<<  "The toDefend has not been successful";
    
    if(testGetCards(player,cards) == 0 )
        std::cout<< "The getCards has been successful";
    else 
        std::cout<< "The getCards has not been successful";
    
    if(testGetOrders(player,orders) == 0 )
        std::cout<< "The getCards has been successful";
    else 
        std::cout<< "The getCards has not been successful";
         
}