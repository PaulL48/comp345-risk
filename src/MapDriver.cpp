#include <iostream>
#include <random>
#include "Map.h"

int main()
{
    // Test set of continents
    std::vector<Continent> testContinents({
        Continent("Continent 1", 4, "yellow"),
        Continent("Continent 2", 5, "blue"),
        Continent("Continent 3", 6, "grey"),
        Continent("Continent 4", 7, "green"),
        Continent("Continent 5", 8, "magenta")
    });

    // Test set of territories
    std::vector<Territory> testTerritories({
        Territory(1, "Territory 1", 1, 2),
        Territory(2, "Territory 2", 3, 4),
        Territory(3, "Territory 3", 5, 6),
        Territory(4, "Territory 4", 7, 8),
        Territory(5, "Territory 5", 9, 10),
        Territory(6, "Territory 6", 11, 12),
        Territory(7, "Territory 7", 13, 14),
        Territory(8, "Territory 8", 15, 16),
        Territory(9, "Territory 9", 17, 18),
        Territory(10, "Territory 10", 19, 20)
    });

    // Base map
    Map baseMap;
    for (const auto& continent : testContinents)
    {
        baseMap.addContinent(continent);
    }

    int continentSelector = 0;
    int groupCount = testTerritories.size() / testContinents.size();
    for (const auto& territory : testTerritories)
    {
        // Distribute the territories into equal groups for the continents
        baseMap.addTerritory(territory, continentSelector++ / groupCount);
    }

    // Build a valid map
    Map validMap = baseMap;
    for (std::size_t i = 0; i < testTerritories.size() - 1; ++i)
    {
        validMap.connectTerritories(i + 1, i + 2);
    }
    std::cout << "State of a valid map: " << validMap.getErrorString(validMap.validate()) << std::endl;

    // Violate connectedness
    // Add random but insufficient connections
    std::random_device randomSource;
    std::mt19937 generator(randomSource());
    std::uniform_int_distribution<> distribution(1, 10);

    // Run randomized test some number of times
    for (std::size_t run = 0; run < 10; ++run)
    {
        Map runMap = baseMap;
        // 8 vertices cannot fully connect a 10 vertex graph
        for (std::size_t i = 0; i < 8; ++i) 
        {
            int t1 = distribution(generator);
            int t2 = distribution(generator);
            runMap.connectTerritories(t1, t2);
            runMap.connectTerritories(t2, t1);
        }
        std::cout << "State of disconnected graph: " << runMap.getErrorString(runMap.validate()) << std::endl;
    }

    // Violate continent connected subgraph
    Map invalidContinents;
    for (const Continent& continent : testContinents)
    {
        invalidContinents.addContinent(continent);
    }

    invalidContinents.addTerritory(testTerritories.at(0), 0);
    invalidContinents.addTerritory(testTerritories.at(1), 0);
    invalidContinents.addTerritory(testTerritories.at(2), 2);
    invalidContinents.addTerritory(testTerritories.at(3), 2);

    invalidContinents.connectTerritories(1, 2);
    invalidContinents.connectTerritories(3, 1);
    invalidContinents.connectTerritories(4, 1);

    std::cout << "State of invalid continent graph: " << invalidContinents.getErrorString(invalidContinents.validate()) << std::endl;


    // Violate Territory not belonging to only one continent
    Map invalidBelonging = baseMap;

    // To achieve this we must prefill a continent
    Continent continent("Continent 5", 9, "salmon");
    continent.addTerritory(testTerritories.at(0));
    invalidBelonging.addContinent(continent);
    for (std::size_t i = 0; i < testTerritories.size() - 1; ++i)
    {
        invalidBelonging.connectTerritories(i + 1, i + 2);
    }
    std::cout << "State of invalid territory ownership map: " << invalidBelonging.getErrorString(invalidBelonging.validate()) << std::endl;

    return 0;
}
