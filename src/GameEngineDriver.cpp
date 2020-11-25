#include <iostream> 

#include "GameEngine.h"
//include "GameStartup.h"
#include "Player.h"

template <typename T>
void addOrder(Player& p)
{
    Order* t = new T();
    t->getMutableDataPayload().player = &p;
    p.getOrders().addToList(*t);
    delete t;
}

int main()
{
    Player p1("Player 1", HumanPlayerStrategy());
    Player p2("Player 2", HumanPlayerStrategy());
    Player p3("Player 3", HumanPlayerStrategy());

    addOrder<Deploy>(p1);
    addOrder<Deploy>(p1);
    addOrder<Deploy>(p1);

    addOrder<Deploy>(p3);

    addOrder<Advance>(p1);
    addOrder<Advance>(p1);
    addOrder<Advance>(p1);

    addOrder<Advance>(p2);
    addOrder<Advance>(p2);
    addOrder<Advance>(p2);

    addOrder<Advance>(p3);
    addOrder<Advance>(p3);
    addOrder<Advance>(p3);

    addOrder<Airlift>(p1);
    addOrder<Blockade>(p2);
    addOrder<Bomb>(p3);

    std::vector<Player> players{p1, p2, p3};
    std::vector<Order*> mol = GameLogic::constructMasterExecutionList(players);
    for (Order* o : mol)
    {
        std::cout << *o << std::endl;
    }
    return 0;


//    int startAgain = 1;

//    while(startAgain == 1)
//    {
//        GameEngine gameEngine;
//        gameEngine.configure();
//        gameEngine.startupPhase();
//        gameEngine.mainGameLoop();

//        GameEngine Start;

//        std::cout << "Would you like the restart the startup phase?" << std::endl;
//        std::cout << "1) YES" << std::endl;
//        std::cout << "2) NO" << std::endl;

//        std::cin >> startAgain;

//        while(startAgain < 1 || startAgain > 2)
//        {
//            std::cout << "Invalid entry. Please enter 1 for YES or 2 for NO" << std::endl; 

//            std::cin >> startAgain;
//        }
//    }

   //std::vector<Player> players= &GameStartup::getPlayers();
   //std::size_t playersInGame = players.size(); 
   //std::cout << "There are currently " << playersInGame << " in the game."
}