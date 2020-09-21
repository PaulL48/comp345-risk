#ifndef MAP_H
#define MAP_H

#include <string>

enum class MapState
{
    VALID,
    NOT_CONNECTED_GRAPH,
    CONTINENTS_NOT_CONNECTED_SUBGRAPHS,
    TERRITORY_BELONGS_TO_MANY_CONTINENTS
};

class Map
{
    // STUB
public:
    MapState validate() const;
    void addContinent(const std::string& name);
    void addTerritory(int id, const std::string& name, int continentId);
    void connectTerritories(int territory1, int territory2);
};

#endif
