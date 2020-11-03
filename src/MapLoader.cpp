//
// Created by Ruslan Dallin on 2020-09-20.
//

#include "MapLoader.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Map MapLoader::loadMap(const std::string &path)
{
    Map map;

    // Check the path is valid
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        std::cout << "Invalid file path supplied\n";
        return map;
    }

    std::ifstream input(path);
    if (input.fail())
    {
        std::cout << path << " opening failed.\n";
        exit(1);
    }

    std::vector<std::string> v = MapLoader::readFile(input);

    // check if valid map file
    std::cout << "Testing : " << path << "\n";
    if (MapLoader::validateFile(v))
        std::cout << "Testing successful \nBuilding Map\n";
    else
    {
        std::cout << "Invalid Map\n";
        return map;
    }

    // Load continents
    MapLoader::addContinents(map, v);
    MapLoader::addTerritories(map, v);
    MapLoader::addBorders(map, v);

    return map;
}

/**
 * Extracting continents from input vector
 * @param v
 * @return
 */
void MapLoader::addContinents(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Extraction Continents\n";
    bool flag = false;
    std::string first;
    std::string item;

    // the following will be used as parameters
    std::string name;
    int armyValue;
    std::string color;

    for (std::string::size_type i = 0; i < v.size(); i++)
    {
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip



        if (v[i].length() == 0 || v[i].at(0) == ';')
            continue;
        // if we reach the next section stop
        if (flag && first == "[countries]")
            break;
        if (flag)
        {
            std::stringstream cc;
            cc << v[i];
            cc >> name;
            cc >> armyValue;
            cc >> color;

            map.addContinent(Continent(name, armyValue, color));
        }
        // if we reach the continents section start creating
        if (first == "[continents]")
            flag = true;
    }
}

/**
 * Extracting territories from input vector
 * @param v
 * @return
 */
void MapLoader::addTerritories(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Extraction Territories\n";
    // std::vector<Territory> territories;
    bool flag = false;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id;
    std::string name;
    int contId;
    int x;
    int y;

    for (std::string::size_type i = 0; i < v.size(); i++)
    {
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip

        if (v[i].length() == 0 || v[i].at(0) == ';')
            continue;
        // if we reach the next section stop
        if (flag && first == "[borders]")
            break;
        if (flag)
        {
            std::stringstream cc;
            cc << v[i];
            cc >> id;
            cc >> name;
            cc >> contId;
            cc >> x;
            cc >> y;
            // constructing territories
            map.addTerritory(Territory(id, name, x, y), contId);
        }
        // if we reach the countries section start creating
        if (first == "[countries]")
            flag = true;
    }
}

/**
 * extracting and adding borders
 * @param v
 */
void MapLoader::addBorders(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Connecting Territories\n";
    bool flag = false;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id;
    int idBorder;

    for (std::string::size_type i = 0; i < v.size(); i++)
    {
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip
        if (v[i].length() == 0 || v[i].at(0) == ';')
            continue;
        if (flag)
        {
            std::stringstream cc;
            cc << v[i];
            cc >> id;

            while (cc >> idBorder)
            {
                map.connectTerritories(id, idBorder);
            }
        }
        // if we reach the borders section start adding borders
        if (first == "[borders]")
            flag = true;
    }
}

/**
 * Helper method. Read file into string vector
 * @param file
 * @return
 */
std::vector<std::string> MapLoader::readFile(std::ifstream &file)
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.length() <= 1)
            continue;
        lines.push_back(line);
    }
    return lines;
}

/**
 * Helper Method. Validate if file is valid map file
 * @param v
 * @return
 */
bool MapLoader::validateFile(const std::vector<std::string> &v)
{
    std::cout << "Verifing Map\n";
    bool continentsSwitch = false;
    bool countriesSwitch = false;
    bool bordersSwitch = false;
    std::string first;

    for (std::string::size_type i = 0; i < v.size(); i++)
    {
        std::stringstream line;
        line << v[i];
        line >> first;
        if (v[i].size() == 0 || v[i].at(0) == ';' || v[i].at(0) == '\r' ||
            v[i].at(0) == '\n')
            continue;
        if (first == "[continents]")
            continentsSwitch = true;
        if (first == "[countries]")
            countriesSwitch = true;
        if (first == "[countries]")
            bordersSwitch = true;
    }
    if (continentsSwitch && countriesSwitch && bordersSwitch)
        return true;
    return false;
}
