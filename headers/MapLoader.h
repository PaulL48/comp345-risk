#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Map.h"
#include <string>

extern const std::string CONQUEST_EXTENSION;
extern const std::string WARZONE_EXTENSION;

namespace MapLoader
{
    Map loadMapValidated(const std::string &path, bool &valid);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    std::vector<std::string> readFile(std::ifstream &file);
    bool validateFile(const std::vector<std::string> &v);
} // namespace MapLoader

// Endpoint of the adapter pattern
class MapReader
{
public:
    MapReader();
    MapReader(const MapReader &reader);
    MapReader &operator=(const MapReader &reader);
    Map read(const std::string &path, bool &valid);
};

// Adapter of the adapter pattern
class MapReaderAdapter
{
public:
    MapReaderAdapter();
    MapReaderAdapter(const MapReaderAdapter &readerAdapter);
    MapReaderAdapter &operator=(const MapReaderAdapter &readerAdapter);
    Map read(const std::string &path, bool &valid);
};

// Adaptee of the adapter pattern
class WarzoneMapReader
{
public:
    WarzoneMapReader();
    WarzoneMapReader(const WarzoneMapReader &reader);
    WarzoneMapReader &operator=(const WarzoneMapReader &reader);
    Map readWarzoneMap(const std::string &path, bool &valid);
};

// Adaptee of the adapter pattern
class ConquestMapReader
{
public:
    ConquestMapReader();
    ConquestMapReader(const ConquestMapReader &reader);
    ConquestMapReader &operator=(const ConquestMapReader &reader);
    Map readConquestMap(const std::string &path, bool &valid);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    bool validateFile(const std::vector<std::string> &fileContents);
};

#endif // MAPLOADER_H
