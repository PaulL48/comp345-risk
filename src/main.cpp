#include <iostream>
#include "Graph.h"

#include <unordered_map>

int main()
{
    Graph<int> g;
    g.insert(1);
    g.insert(2);
    g.insert(3);
    g.connect(1, 2);
    g.connect(1, 3);
    g.connect(2, 3);
    g.connect(3, 1);

    g.iter_dfs();

    return 0;
}

