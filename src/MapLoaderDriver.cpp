//
// Created by Ruslan Dallin on 2020-09-20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "MapLoader.h"

int main()
{
    for (auto& directoryEntry : std::filesystem::directory_iterator("./maps"))
    {
        std::string fileName = directoryEntry.path().string();
        Map map = MapLoader::loadMap(fileName);
        std::cout << "Map file \"" << fileName << "\" status: " << map.getErrorString(map.validate()) << "\n";
        std::cout << "\n";
    }
    return 0;
}




