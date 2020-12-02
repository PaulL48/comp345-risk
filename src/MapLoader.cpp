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
#include <algorithm>

Map MapLoader::loadMapValidated(const std::string &path, bool &valid)
{
    Map map;
    // Check the path is valid
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        std::cout << "Invalid file path supplied\n";
        valid = false;
        return map;
    }

    std::ifstream input(path);
    if (input.fail())
    {
        std::cout << path << " opening failed.\n";
        valid = false;
        exit(1);
    }

    std::vector<std::string> v = MapLoader::readFile(input);

    // check if valid map file
    std::cout << "Testing : " << path << "\n";
    if (MapLoader::validateFile(v))
        std::cout << "Testing successful \nBuilding Map\n";
    else
    {
        std::cout << "Invalid Map, please start again.\n";
        valid = false;
        return map;
    }

    // Load continents
    MapLoader::addContinents(map, v);
    MapLoader::addTerritories(map, v);
    MapLoader::addBorders(map, v);
    valid = true;

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
    std::cout << "Verifing Map file\n";
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

//==================================================================================================
//                                              MapReader Class
//==================================================================================================

MapReader::MapReader()
{
}

MapReader::MapReader(const MapReader &)
{
}

MapReader &MapReader::operator=(const MapReader &)
{
    return *this;
}

Map MapReader::read(const std::string &path, bool &valid)
{
    return MapReaderAdapter().read(path, valid);
}

//==================================================================================================
//                                              MapReaderAdapter Class
//==================================================================================================

MapReaderAdapter::MapReaderAdapter()
{
}

MapReaderAdapter::MapReaderAdapter(const MapReaderAdapter &)
{
}

MapReaderAdapter &MapReaderAdapter::operator=(const MapReaderAdapter &)
{
    return *this;
}

Map MapReaderAdapter::read(const std::string &path, bool &valid)
{
    std::string extension = path.substr(path.find_last_of(".") + 1);
    if (extension == CONQUEST_EXTENSION)
    {
        std::cout << "Standby, loading conquest map..." << std::endl;
        return ConquestMapReader().readConquestMap(path, valid);
    }
    else if (extension == WARZONE_EXTENSION)
    {
        std::cout << "Standby, loading warzone map..." << std::endl;
        return WarzoneMapReader().readWarzoneMap(path, valid);
    }
    else
    {
        std::cout << "Unsupported map type extension: " << extension << std::endl;
        return Map();
    }
}

//==================================================================================================
//                                              WarzoneMapReader Class
//==================================================================================================

WarzoneMapReader::WarzoneMapReader()
{
}

WarzoneMapReader::WarzoneMapReader(const WarzoneMapReader &)
{
}

WarzoneMapReader &WarzoneMapReader::operator=(const WarzoneMapReader &)
{
    return *this;
}

Map WarzoneMapReader::readWarzoneMap(const std::string &path, bool &valid)
{
    return MapLoader::loadMapValidated(path, valid);
}

//==================================================================================================
//                                              ConquestMapReader Class
//==================================================================================================

ConquestMapReader::ConquestMapReader()
{
}

ConquestMapReader::ConquestMapReader(const ConquestMapReader &)
{
}

ConquestMapReader &ConquestMapReader::operator=(const ConquestMapReader &)
{
    return *this;
}

Map ConquestMapReader::readConquestMap(const std::string &path, bool &valid)
{
    Map map;
    // Check the path is valid
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        std::cout << "Invalid file path supplied\n";
        valid = false;
        return map;
    }

    std::ifstream input(path);
    if (input.fail())
    {
        std::cout << path << " opening failed.\n";
        valid = false;
        exit(1);
    }

    std::vector<std::string> v = MapLoader::readFile(input);

    // check if valid map file
    std::cout << "Testing : " << path << "\n";
    if (this->validateFile(v))
    {
        std::cout << "Testing successful \nBuilding Map\n";
    }
    else
    {
        std::cout << "Invalid Map, please start again.\n";
        valid = false;
        return map;
    }

    // Load continents
    this->addContinents(map, v);
    this->addTerritories(map, v);
    this->addBorders(map, v);
    valid = true;

    return map;
}

/**
 * Extracting continents from input vector
 * @param v
 * @return
 */
void ConquestMapReader::addContinents(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Extraction Continents\n";
    bool flag = false;
    std::string first;

    for (std::string::size_type i = 0; i < v.size(); i++)
    {
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip

        if (v[i].length() == 0 || v[i].at(0) == ';')
            continue;
        // if we reach the next section stop
        if (flag && first == "[Territories]")
            break;
        if (flag)
        {
            std::size_t separator = v[i].find('=');
            std::string name = v[i].substr(0, separator);
            std::string bonus = v[i].substr(separator + 1);
            int parsedBonus = -1;

            try
            {
                parsedBonus = std::stoi(bonus);
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                std::exit(1);
            }

            map.addContinent(Continent(name, parsedBonus, "none"));

        }
        // if we reach the continents section start creating
        if (first == "[Continents]")
            flag = true;
    }
}

/**
 * Extracting territories from input vector
 * @param v
 * @return
 */
void ConquestMapReader::addTerritories(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Extraction Territories\n";
    // std::vector<Territory> territories;
    bool flag = false;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id = 0;
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
        if (flag)
        {
            std::stringstream cc;
            cc << v[i];
            std::string token;
            std::vector<std::string> line;

            while(std::getline(cc, token, ',')) {
                line.push_back(token);
            }

            name = line.at(0);
            contId = map.getContinentIdByName(line.at(3));
            x = std::stoi(line.at(1));
            y = std::stoi(line.at(2));

            // constructing territories
            map.addTerritory(Territory(id, name, x, y), contId);
            id++;

        }
        // if we reach the countries section start creating
        if (first == "[Territories]")
            flag = true;
    }
}

/**
 * extracting and adding borders
 * @param v
 */
void ConquestMapReader::addBorders(Map &map, const std::vector<std::string> &v)
{
    std::cout << "Connecting Territories\n";
    bool flag = false;
    std::string first;
    std::string item;
    std::string borderingTerritory;

    // the following will be used as parameters
    int id = 0;

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
            std::string token;
            std::vector<std::string> line;

            while(std::getline(cc, token, ',')) {
                line.push_back(token);
            }

            for (std::string::size_type i = 4; i < line.size(); i++){
                // std::cout << "Connecting territory " << i << " with name: " << line.at(i) << std::endl;
                // map.connectTerritories(id, map.getTerritoryIdByName(line.at(i)));
                // std::cout << "Connecting territory " << map.getTerritoryIdByName(line.at(i)) << " with name: " << i << std::endl;
                // map.connectTerritories(map.getTerritoryIdByName(line.at(i)), id);
                
                int territoryId1 = map.getTerritoryIdByName(line.at(0));
                int territoryId2 = map.getTerritoryIdByName(line.at(i));

                std::cout << "Connecting " << territoryId1 << " to " << territoryId2 << std::endl;
                map.connectTerritories(territoryId1, territoryId2);
            }

            id++;
        }
        // if we reach the borders section start adding borders
        if (first == "[Territories]")
            flag = true;
    }
}

/**
 * Helper Method. Validate if file is valid map file
 * @param v
 * @return
 */
bool ConquestMapReader::validateFile(const std::vector<std::string> &fileContents)
{
    std::cout << "Verifing Map file\n";
    bool continentsSwitch = false;
    bool countriesSwitch = false;
    std::string first;

    for (std::string::size_type i = 0; i < fileContents.size(); i++)
    {
        std::stringstream line;
        line << fileContents[i];
        line >> first;
        if (fileContents[i].size() == 0 || fileContents[i].at(0) == ';' || fileContents[i].at(0) == '\r' ||
            fileContents[i].at(0) == '\n')
            continue;
        if (first == "[Continents]")
            continentsSwitch = true;
        if (first == "[Territories]")
            countriesSwitch = true;
    }
    if (continentsSwitch && countriesSwitch)
        return true;
    return false;
}
