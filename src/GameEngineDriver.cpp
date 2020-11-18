#include <iostream> 

#include "GameEngine.h"
//include "GameStartup.h"
#include "Player.h"

int main()
{
    int startAgain = 1;

    while(startAgain == 1)
    {
        GameEngine Start;  

        std::cout << "Would you like the restart the startup phase?" << std::endl;
        std::cout << "1) YES" << std::endl;
        std::cout << "2) NO" << std::endl;

        std::cin >> startAgain;

        while(startAgain < 1 || startAgain > 2)
        {
            std::cout << "Invalid entry. Please enter 1 for YES or 2 for NO" << std::endl; 

            std::cin >> startAgain;
        }
    }

    std::cout << "The game has been initialized" << std::endl; 

    //std::vector<Player> players= &GameStartup::getPlayers();
    //std::size_t playersInGame = players.size(); 
    //std::cout << "There are currently " << playersInGame << " in the game."
}