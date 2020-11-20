//
// Created by Ruslan Dallin on 2020-09-20.
//

#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"
#include <string>

namespace MapLoader
{
    Map createMap(const std::string &path);
    Map loadMap(Map &map, const std::string &path);

    Map loadMapValidated(const std::string& path, bool& valid);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    std::vector<std::string> readFile(std::ifstream &file);
    bool validateFile(const std::vector<std::string> &v);
} // namespace MapLoader

#endif // MAPLOADER_H
