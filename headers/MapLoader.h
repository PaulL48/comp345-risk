//
// Created by Ruslan Dallin on 2020-09-20.
//

#ifndef MAPLOADER_H
#define MAPLOADER_H
#include <string>
#include "Map.h"

// class Continent{
// public:
//     Continent(int idPar, const std::string &namePar, int armyValuePar, const std::string &colorPar);
//     Continent(const Continent &continent);
//     Continent &operator =(const Continent &rightSide);
//     ~Continent();
//     friend std::ostream& operator<<(std::ostream &strm, const Continent &a);
//     static std::vector<Continent> extractContinents(const std::vector<std::string> &vParm);
//     static void addContinents(const std::vector<Continent> &v);

// private:
//     int *id;
//     std::string *name;
//     int *armyValue;
//     std::string *color;

// };

// class Territory {
// public:
//     Territory(int idPar, const std::string &namePar, int contIdPar, int xPar, int yPar);
//     Territory(const Territory &territory);
//     Territory &operator =(const Territory &rightSide);
//     static std::vector<Territory> extractTerritories(const std::vector<std::string> &v);
//     friend std::ostream& operator<<(std::ostream &strm, const Territory &a);
//     static void addTerritories(const std::vector<Territory> &v);
//     static void addBorders(const std::vector<std::string> &v);
//     ~Territory();

// private:
//     int *id;
//     std::string *name;
//     int *contId;
//     int *x;
//     int *y;
// };

namespace MapLoader
{
    Map loadMap(const std::string& path);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    std::vector<std::string> readFile(std::ifstream& file);
    bool validateFile(const std::vector<std::string> &v);
    std::vector<std::string> split(const std::string &str, char delimiter);
}

#endif //MAPLOADER_H

