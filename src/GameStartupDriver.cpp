#include "Map.h"
#include <iostream>
#include <random>
#include "GameStartup.h"

int main(){

}
std::vector<Continent> testContinents({Continent("Continent 1", 4, "yellow"),
                                       Continent("Continent 2", 5, "blue"),
                                       Continent("Continent 3", 6, "grey"),
                                       Continent("Continent 4", 7, "green"),
                                       Continent("Continent 5", 8, "magenta")});
GameStartup game = GameStartup();

std::vector<Territory> testTerritories(
    {Territory(1, "Territory 1", 1, 2), Territory(2, "Territory 2", 3, 4),
     Territory(3, "Territory 3", 5, 6), Territory(4, "Territory 4", 7, 8),
     Territory(5, "Territory 5", 9, 10), Territory(6, "Territory 6", 11, 12),
     Territory(7, "Territory 7", 13, 14), Territory(8, "Territory 8", 15, 16),
     Territory(9, "Territory 9", 17, 18), Territory(10, "Territory 10", 19, 20)});

Map map;
for(Continent continent : testContinents)
{
    map.addContinent(continent);
}

int groupCount = testTerritories.size() / testContinents.size();
int continentSelector = groupCount;
for (const auto &territory : testTerritories)
{
    // Distribute the territories into equal groups for the continents
    map.addTerritory(territory, continentSelector++ / groupCount);
}
// Build a valid map
Map validMap = map;
for (std::size_t i = 0; i < testTerritories.size() - 1; ++i)
{
    validMap.connectTerritories(i + 1, i + 2);
}
