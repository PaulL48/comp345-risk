//#include "GameEngine.h"
//#include "Map.h"
//#include <iostream>
//#include <random>
//
//
//int main()
//{
//    std::vector<Continent> testContinents(
//        {Continent("Continent 1", 4, "yellow"), Continent("Continent 2", 5, "blue"),
//         Continent("Continent 3", 6, "grey"), Continent("Continent 4", 7, "green"),
//         Continent("Continent 5", 8, "magenta")});
//
//    std::vector<Territory> testTerritories(
//        {Territory(1, "Territory 1", 1, 2), Territory(2, "Territory 2", 3, 4),
//         Territory(3, "Territory 3", 5, 6), Territory(4, "Territory 4", 7, 8),
//         Territory(5, "Territory 5", 9, 10), Territory(6, "Territory 6", 11, 12),
//         Territory(7, "Territory 7", 13, 14), Territory(8, "Territory 8", 15, 16),
//         Territory(9, "Territory 9", 17, 18), Territory(10, "Territory 10", 19, 20)});
//
//    Map map;
//    for (Continent continent : testContinents)
//    {
//        map.addContinent(continent);
//    }
//
//    int groupCount = testTerritories.size() / testContinents.size();
//    int continentSelector = groupCount;
//    for (const auto &territory : testTerritories)
//    {
//        // Distribute the territories into equal groups for the continents
//        map.addTerritory(territory, continentSelector++ / groupCount);
//    }
//    // Build a valid map
//    Map validMap = map;
//    for (std::size_t i = 0; i < testTerritories.size() - 1; ++i)
//    {
//        validMap.connectTerritories(i + 1, i + 2);
//    }
//
//    GameStartup game = GameStartup(4,validMap);
//    game.startupPhase();
//    for(Territory terr : game.getMap().getGraph()){
//        if(terr.getOwningPlayer() != nullptr){
//             const Player& p = *(terr.getOwningPlayer());
//             std::cout<< p.getPlayerName() + " OWNS THE FOLLOWING TERRITORY : \n";
//             std::cout << terr;
//             std::cout<< std::endl;
//        }
//        else{
//           std::cout << "TERRITORIES ASSIGNMENT HAS FAILED \n";
//        }
//    }
//    for(Player player : game.getPlayers()){
//        std::string s = player.getPlayerName();
//    
//        std::cout<< player.getPlayerName() + " has the following amount of Armies " + std::to_string(player.getReinforcementPool()) + " \n";
//    }
//
//    for(Player player: game.getPlayers()){
//
//        std::cout << "OUTPUTING THE PLAYING ORDER CONTAINED IN THE FOLLOWING PLAYER : " + player.getPlayerName() + " \n";
//        int count =  0;
//        for(int index: player.getPlayerOrder()){
//            std::cout<<  std::to_string(count+1) + ":  PLAYER " + std::to_string(index+1) + "  ";
//            count++;
//
//        } 
//        std::cout<< std::endl;
//
//        
//    }
//
//
//
//}
//