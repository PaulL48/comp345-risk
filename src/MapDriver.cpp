#include <iostream>
#include <random>
#include "Map.h"

int main()
{
    Graph<int> g;
    g.insert(1);
    g.insert(2);
    g.insert(3);
    g.insert(4);
    g.connect(1, 2);
    g.connect(1, 3);
    g.connect(2, 4);
    g.connect(3, 1);
    g.connect(4, 2);
    std::cout << "Graph: " << g << std::endl;

    g.merge(1, 2);
    std::cout << "Graph: " << g << std::endl;

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
        validMap.connectTerritories(i + 2, i + 1);
    }

    std::cout << "validMap state: " << validMap.getErrorString(validMap.validate()) << std::endl;

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

        std::cout << "runMap state: " << runMap.getErrorString(runMap.validate()) << std::endl;
    }

    // Violate continent connected subgraph
    Map continentsNotValid;
    for (const Continent& continent : testContinents)
    {
        continentsNotValid.addContinent(continent);
    }

    continentsNotValid.addTerritory(testTerritories.at(0), 0);
    continentsNotValid.addTerritory(testTerritories.at(1), 0);

    // Violate Territory belongs to many continents

    return 0;
}

// TODO: Uncomment before delivery
// int main()
// {
//     Graph<int> g;
//     g.insert(4);
//     g.insert(1);
//     g.insert(2);
//     g.insert(3);
    
//     g.connect(1, 2);
//     g.connect(1, 1);
//     g.connect(1, 4);
//     g.connect(1, 3);
//     g.connect(2, 3);
//     g.connect(3, 1);
//     std::cout << g << std::endl;


//     Graph<int> subg;
//     subg.insert(1);
//     subg.insert(2);
//     subg.connect(1, 2);
//     subg.connect(1, 1);


//     std::cout << "Graph connected? " << g.isConnected() << std::endl;
//     std::cout << "Is subgraph? " << subg.isSubgraphOf(g) << std::endl;

//     int i = 3;
//     int j = 9;
//     std::unordered_set<int*> test;
//     test.insert(&i);
//     test.insert(&j);

//     std::unordered_set<int> ttest;
//     ttest.insert(4);
//     ttest.insert(5);
//     std::cout << test << std::endl;
//     std::cout << ttest << std::endl;
    
//     for (const int& vertex: g)
//     {
//         std::cout << vertex << std::endl;
//     }

//     std::cout << g.begin() << std::endl;

//     return 0;
//     return 0;
// }
