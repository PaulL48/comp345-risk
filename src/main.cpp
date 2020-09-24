#include <iostream>
#include "Graph.h"

#include <unordered_map>

int main()
{
    Graph<int> g;
    g.insert(4);
    g.insert(1);
    g.insert(2);
    g.insert(3);
    
    g.connect(1, 2);
    g.connect(1, 1);
    g.connect(1, 4);
    g.connect(1, 3);
    g.connect(2, 3);
    g.connect(3, 1);
    std::cout << g << std::endl;


    Graph<int> subg;
    subg.insert(1);
    subg.insert(2);
    subg.connect(1, 2);
    subg.connect(1, 1);


    std::cout << "Graph connected? " << g.isConnected() << std::endl;
    std::cout << "Is subgraph? " << subg.isSubgraphOf(g) << std::endl;
    
    std::unordered_map<int, int> i;
    for (const int& vertex: g)
    {
        std::cout << vertex << std::endl;
    }

    return 0;
}

