// //
// // Created by Ruslan Dallin on 2020-09-20.
// //

// #include "MapLoader.h"
// #include <filesystem>
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <vector>

// int main()
// {
//     for (auto &directoryEntry : std::filesystem::directory_iterator("./maps"))
//     {
//         std::string fileName = directoryEntry.path().string();
//         Map map = MapLoader::loadMap(fileName);
//         std::cout << "Map file \"" << fileName
//                   << "\" status: " << map.getErrorString(map.validate()) << "\n";
//         std::cout << "\n";
//     }
//     return 0;
// }
