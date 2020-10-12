//#include "Map.h"
//
////============================================================================================================================================================
//// CLASS DEFINITIONS: Territory
////============================================================================================================================================================
//
//Territory::Territory() :
//    id(new int(-1)),
//    name(new std::string()),
//    x(new int(0)),
//    y(new int(0)),
//    occupyingArmies(new int(0)),
//    ownedBy(nullptr)
//{
//}
//
//Territory::Territory(int id, const std::string &name, int x, int y) :
//    id(new int(id)),
//    name(new std::string(name)),
//    x(new int(x)),
//    y(new int(y)),
//    occupyingArmies(new int(0)),
//    ownedBy(nullptr)
//{
//}
//
//Territory::Territory(const Territory &territory) :
//    id(new int(*territory.id)),
//    name(new std::string(*territory.name)),
//    x(new int(*territory.x)),
//    y(new int(*territory.y)),
//    occupyingArmies(new int(*territory.occupyingArmies)),
//    ownedBy(territory.ownedBy)
//{
//}
//
//Territory::~Territory()
//{
//    // Non-owning pointer ownedBy is not deleted
//    delete this->id;
//    delete this->name;
//    delete this->x;
//    delete this->y;
//    delete this->occupyingArmies;
//}
//
//Territory &Territory::operator=(const Territory &territory)
//{
//    if (&territory == this)
//    {
//        return *this;
//    }
//
//    *this->id = *territory.id;
//    *this->name = *territory.name;
//    *this->x = *territory.x;
//    *this->y = *territory.y;
//    *this->occupyingArmies = *territory.occupyingArmies;
//    this->ownedBy = territory.ownedBy;
//    return *this;
//}
//
//bool Territory::operator==(const Territory &territory) const
//{
//    return (*this->id == *territory.id && *this->name == *territory.name);
//}
//
//bool Territory::operator!=(const Territory &territory) const
//{
//    return !(*this == territory);
//}
//
//int Territory::getId() const
//{
//    return *this->id;
//}
//
//std::ostream &operator<<(std::ostream &output, const Player &player)
//{
//    // STUB
//    output << player.name;
//    return output;
//}
//
//std::ostream &operator<<(std::ostream &output, const Territory &territory)
//{
//    output << "(id:" << *territory.id << ", name:" << *territory.name;
//    if (territory.ownedBy != nullptr)
//    {
//        output << ", owning player:" << *territory.ownedBy;
//        output << ", armies:" << *territory.occupyingArmies;
//    }
//    output << ")";
//    return output;
//}
//
////============================================================================================================================================================
//// CLASS DEFINITIONS: Continent
////============================================================================================================================================================
//
//Continent::Continent(const std::string &name, int armyValue, const std::string &color) :
//    name(new std::string(name)),
//    armyValue(new int(armyValue)),
//    color(new std::string(color)),
//    territories(new Graph<Territory>())
//{
//}
//
//Continent::Continent(const Continent &continent) :
//    name(new std::string(*continent.name)),
//    armyValue(new int(*continent.armyValue)),
//    color(new std::string(*continent.color)),
//    territories(new Graph<Territory>(*continent.territories))
//{
//}
//
//Continent::~Continent()
//{
//    delete this->name;
//    delete this->armyValue;
//    delete this->color;
//    delete this->territories;
//}
//
//Continent &Continent::operator=(const Continent &continent)
//{
//    if (&continent == this)
//    {
//        return *this;
//    }
//
//    *this->name = *continent.name;
//    *this->territories = *continent.territories;
//    *this->armyValue = *continent.armyValue;
//    *this->color = *continent.color;
//    return *this;
//}
//
//bool Continent::isValidContinent(const Graph<Territory> &territories) const
//{
//    return this->territories->isConnected() &&
//           this->territories->isSubgraphOf(territories);
//}
//
//void Continent::connectTerritories(const Territory &territory1,
//                                   const Territory &territory2)
//{
//    this->territories->connect(territory1, territory2);
//}
//
//void Continent::addTerritory(const Territory &territory)
//{
//    this->territories->insert(territory);
//}
//
//DepthFirstIterator<Territory> Continent::begin() const
//{
//    return this->territories->begin();
//}
//
//DepthFirstIterator<Territory> Continent::end() const
//{
//    return this->territories->end();
//}
//
//std::ostream &operator<<(std::ostream &output, const Continent &continent)
//{
//    output << "( name: " << *continent.name;
//    output << ", territories: " << *continent.territories;
//    output << ", army value: " << *continent.armyValue;
//    output << ", color: " << *continent.color;
//    output << ")";
//    return output;
//}
//
////============================================================================================================================================================
//// CLASS DEFINITIONS: Map
////============================================================================================================================================================
//
//Map::Map() :
//    territories(new Graph<Territory>()), continents(new std::vector<Continent>())
//{
//}
//
//Map::Map(const Map &map) :
//    territories(new Graph<Territory>(*map.territories)),
//    continents(new std::vector<Continent>(*map.continents))
//{
//}
//
//Map::~Map()
//{
//    delete territories;
//    delete continents;
//}
//
//Map &Map::operator=(const Map &map)
//{
//    *this->territories = *map.territories;
//    *this->continents = *map.continents;
//    return *this;
//}
//
//MapState Map::validate() const
//{
//    if (!this->territories->isConnected())
//    {
//        return MapState::NOT_CONNECTED_GRAPH;
//    }
//
//    // To check that continents are connected subgraphs:
//    // Merge all nodes for each continent into a single node (maintaining edges)
//    // if the resulting graph is connected, then continents are connected subgraphs
//    Graph<Territory> continentGraph = *this->territories;
//    for (const Continent &continent : *this->continents)
//    {
//        // We collapse it down to the first node
//        auto it = continent.begin();
//        if (it == continent.end())
//        {
//            continue;
//        }
//
//        for (auto nextIt = it + 1; nextIt != continent.end(); ++nextIt)
//        {
//            continentGraph.merge(*it, *nextIt);
//        }
//    }
//
//    if (!continentGraph.isConnected())
//    {
//        return MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS;
//    }
//
//    // Second check to make sure each continent is connected within themselves
//    for (const Continent &continent : *this->continents)
//    {
//        if (!continent.isValidContinent(*this->territories))
//        {
//            return MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS;
//        }
//    }
//
//    // Scan through territories via continents and flag the error when a territory
//    // is seen twice
//    // Assure each territory is in one and only one continent
//
//    std::unordered_set<Territory> territories;
//    for (const Continent &continent : *this->continents)
//    {
//        for (const Territory &territory : continent)
//        {
//            if (territories.count(territory) == 0)
//            {
//                territories.insert(territory);
//            }
//            else
//            {
//                return MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET;
//            }
//        }
//    }
//
//    // Check for a territory that is not part of a continent
//    for (const Territory &territory : *this->territories)
//    {
//        if (territories.count(territory) == 0)
//        {
//            return MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET;
//        }
//    }
//
//    return MapState::VALID;
//}
//
//std::string Map::getErrorString(MapState mapState) const
//{
//    switch (mapState)
//    {
//    case MapState::VALID:
//        return "Map contains no errors";
//    case MapState::NOT_CONNECTED_GRAPH:
//        return "Map is not a connected graph";
//    case MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS:
//        return "Map continents are not all connected subgraphs of the territories";
//    case MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET:
//        return "Some map territories do not belong to only one continent";
//    default:
//        return "Invalid MapState Error code";
//    }
//}
//
//void Map::addContinent(const Continent &continent)
//{
//    this->continents->push_back(continent);
//}
//
//void Map::addTerritory(const Territory &territory, int continentId)
//{
//    this->territories->insert(territory);
//    this->continents->at(continentId).addTerritory(territory);
//}
//
//void Map::connectTerritories(int territoryId1, int territoryId2)
//{
//    auto findTerritory1 = [territoryId1](const Territory &t) {
//        return t.getId() == territoryId1;
//    };
//    auto findTerritory2 = [territoryId2](const Territory &t) {
//        return t.getId() == territoryId2;
//    };
//    const Territory *territory1 = this->territories->findIf(findTerritory1);
//    const Territory *territory2 = this->territories->findIf(findTerritory2);
//    if (territory1 == nullptr || territory2 == nullptr)
//    {
//        // These territories do not yet exist
//        return;
//    }
//
//    this->territories->connect(*territory1, *territory2);
//    for (Continent &continent : *this->continents)
//    {
//        continent.connectTerritories(*territory1, *territory2);
//    }
//}
//
//std::ostream &operator<<(std::ostream &output, const Map &map)
//{
//    output << "(territories: " << *map.territories
//           << ", continents: " << *map.continents << ")";
//    return output;
//}
