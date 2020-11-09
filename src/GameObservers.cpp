//
// Created by Ruslan Dallin on 2020-11-03.
//

#include "map.h"
#include "MapLoader.h"

int main()
{
    Map map = MapLoader::loadMap("../maps/trivia.map");
    std::cout << map;
    return 0;
}
