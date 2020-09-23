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
    

    for (auto it = g.begin(); it != g.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}

