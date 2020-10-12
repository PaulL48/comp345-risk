#include  "Player.h"
#include <iostream>
#include <vector>
#include <string>
int testGetPlayerName(Player player, std::string* playerName){
    if(player.getPlayerName() == (*playerName)){
        return 0;
    }
    else
        return 1;
}
int testGetAttackTerriotories(Player player, std::vector<Territory>* attackTerritories){
    if(player.toAttack() == *(attackTerritories))
        return 0;
    else
        return 1;
}
int testGetAttackDefendTerritories(Player player, std::vector<Territory>* defendTerritories){
    if(player.toDefend() == *(defendTerritories))
        return 0;
    else
        return 1;
}
int testGetCards(Player player, Hand cards){
    if(cards.handSize() == player.getCards().handSize())
        return 0;
    else
        return 1;
}

int main(){
   std::vector<Territory>* initialAttackTerritories = new std::vector<Territory>(
         {Territory(1, "Territory 1", 1, 2), Territory(2, "Territory 2", 3, 4),
          Territory(3, "Territory 3", 5, 6), Territory(4, "Territory 4", 7, 8),
          Territory(5, "Territory 5", 9, 10), Territory(6, "Territory 6", 11, 12),
          Territory(7, "Territory 7", 13, 14), Territory(8, "Territory 8", 15, 16),
          Territory(9, "Territory 9", 17, 18), Territory(10, "Territory 10", 19, 20)});
     std::vector<Territory>* initialDefendTerritories = new std::vector<Territory>(
         {Territory(1, "Territory 1", 1, 2), Territory(2, "Territory 2", 3, 4),
          Territory(3, "Territory 3", 5, 6), Territory(4, "Territory 4", 7, 8),
          Territory(5, "Territory 5", 9, 10), Territory(6, "Territory 6", 11, 12),
          Territory(7, "Territory 7", 13, 14), Territory(8, "Territory 8", 15, 16),
          Territory(9, "Territory 9", 17, 18), Territory(10, "Territory 10", 19, 20)});

    std::string* playerName = new std::string("Sammy");
    Card *cardDrawn;
    Deck deck;
    Hand hand;
    for (int i = 0; i < 5; i++)
    {
         cardDrawn = deck.draw();
         hand.addToHand(cardDrawn);
        
    }

    OrdersList orderlist;
    Deploy deploy;
    Bomb bomb;
    Airlift airlift;
    Blockade blockade;
    orderlist.addToList(deploy);
    orderlist.addToList(bomb);
    orderlist.addToList(airlift);
    orderlist.addToList(blockade);


    Player player = Player(*playerName, *initialAttackTerritories,*initialDefendTerritories,hand,orderlist);

    if(testGetPlayerName(player,playerName) == 0)
        std::cout << "The GetPlayerName has been successful " <<std::endl;
    else
        std::cout<< "The GetPlayerName has not been successful " <<std::endl;

    if(testGetAttackTerriotories(player, initialAttackTerritories) == 0)
        std::cout<< "The toAttack has been successful"<<std::endl;
    else
        std::cout<< "The toAttack has not been successful"<<std::endl;

    if(testGetAttackDefendTerritories(player,initialDefendTerritories) == 0)
        std::cout<<  "The toDefend has been successful"<<std::endl;
    else
        std::cout<<  "The toDefend has not been successful"<<std::endl;

    if(testGetCards(player,hand) == 0 )
        std::cout<< "The getCards has been successful"<<std::endl;
    else
        std::cout<< "The getCards has not been successful"<<std::endl;

    player.issueOrder();
    std::cout<<"The issue order has been successful"<<std::endl;

}