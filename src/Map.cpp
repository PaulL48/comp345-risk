#include "Map.h"

//============================================================================================================================================================
// CLASS DEFINITIONS: Territory
//============================================================================================================================================================

Territory::Territory() : id(new int(-1)),
                         name(new std::string()),
                         occupyingArmies(new int(0)),
                         ownedBy(nullptr)
{
}

Territory::Territory(int id, const std::string& name) : id(new int(id)),
                                                        name(new std::string(name)),
                                                        occupyingArmies(new int(0)),
                                                        ownedBy(nullptr)
{
}

Territory::Territory(const Territory& territory) : id(new int(*territory.id)),
                                                   name(new std::string(*territory.name)),
                                                   occupyingArmies(new int(*territory.occupyingArmies)),
                                                   ownedBy(territory.ownedBy)
{
}

Territory::~Territory()
{
    delete this->id;
    delete this->name;
    delete this->occupyingArmies;
    // Non-owning pointer ownedBy is not deleted
}

Territory& Territory::operator=(const Territory& territory)
{
    if (&territory == this)
    {
        return *this;
    }

    *this->id = *territory.id;
    *this->name = *territory.name;
    *this->occupyingArmies = *territory.occupyingArmies;
    this->ownedBy = territory.ownedBy;
    return *this;
}

bool Territory::operator==(const Territory& territory) const
{
    return (*this->id == *territory.id && *this->name == *territory.name);
}

int Territory::getId() const
{
    return *this->id;
}

std::ostream& operator<<(std::ostream& output, const Player& player)
{
    // STUB
    output << player.name;
    return output;
}

std::ostream& operator<<(std::ostream& output, const Territory& territory)
{
    output << "(id:" << *territory.id << ", name:" << *territory.name << ", owning player:" << *territory.ownedBy << ", armies:" << *territory.occupyingArmies << ")";
    return output;
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Continent
//============================================================================================================================================================

Continent::Continent(const std::string& name) : name(new std::string(name))
{
}

Continent::Continent(const Continent& continent) : name(new std::string(*continent.name))
{
}

Continent::~Continent()
{
    delete this->name;
}

Continent& Continent::operator=(const Continent& continent)
{
    if (&continent == this)
    {
        return *this;
    }

    *this->name = *continent.name;
    *this->territories = *continent.territories;
    return *this;
}

bool Continent::isValidContinent(const Graph<Territory>& territories) const
{
    return this->territories->isConnected() && this->territories->isSubgraphOf(territories);
}

void Continent::connectTerritories(const Territory& territory1, const Territory& territory2)
{
    this->territories->connect(territory1, territory2);
}

void Continent::addTerritory(const Territory& territory)
{
    this->territories->insert(territory);
}

DepthFirstIterator<Territory> Continent::begin() const
{
    return this->territories->begin();
}

DepthFirstIterator<Territory> Continent::end() const
{
    return this->territories->end();
}

std::ostream& operator<<(std::ostream& output, const Continent& continent)
{
    output << "( name: " << continent.name << ", territories: " << continent.territories << ")";
    return output;
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Map
//============================================================================================================================================================

MapState Map::validate() const
{
    if (!this->territories->isConnected())
    {
        return MapState::NOT_CONNECTED_GRAPH;
    }

    for (const Continent& continent : *this->continents)
    {
        if (!continent.isValidContinent(*this->territories))
        {
            return MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS;
        }
    }

    std::unordered_set<Territory> territories;
    for (const Continent& continent : *this->continents)
    {
        for (const Territory& territory : continent)
        {
            if (territories.count(territory) == 0)
            {
                territories.insert(territory);
            }
            else
            {
                return MapState::TERRITORY_BELONGS_TO_MANY_CONTINENTS;
            }
        }
    }

    return MapState::VALID;
}

void Map::addContinent(const std::string& name)
{
    this->continents->push_back(Continent(name));
}

void Map::addTerritory(int id, const std::string& name, int continentId)
{
    this->territories->insert(Territory(id, name));
    this->continents->at(continentId).addTerritory(Territory(id, name));
}

void Map::connectTerritories(int territoryId1, int territoryId2)
{
    const Territory* territory1 = this->territories->find_if([territoryId1](const Territory& t){return t.getId() == territoryId1;});
    const Territory* territory2 = this->territories->find_if([territoryId2](const Territory& t){return t.getId() == territoryId2;});
    if (territory1 == nullptr || territory2 == nullptr)
    {
        // These territories do not yet exist
        return;
    }

    this->territories->connect(*territory1, *territory2);
    for (Continent& continent : *this->continents)
    {
        continent.connectTerritories(*territory1, *territory2);
    }
}

std::ostream& operator<<(std::ostream& output, const Map& map)
{
    output << "(territories: " << *map.territories << ", continents: " << *map.continents << ")";
    return output;
}
