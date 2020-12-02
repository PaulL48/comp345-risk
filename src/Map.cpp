#include "Map.h"
#include "MapLoader.h"
#include "Player.h"

//============================================================================================================================================================
// CLASS DEFINITIONS: Territory
//============================================================================================================================================================

Territory::Territory() :
    id(new int(-1)),
    name(new std::string()),
    x(new int(0)),
    y(new int(0)),
    occupyingArmies(new int(0)),
    ownedBy(nullptr)
{
}

Territory::Territory(int id, const std::string &name, int x, int y) :
    id(new int(id)),
    name(new std::string(name)),
    x(new int(x)),
    y(new int(y)),
    occupyingArmies(new int(0)),
    ownedBy(nullptr)
{
}

Territory::Territory(int id, const std::string &name, int numberOfTerritories, int x,
                     int y, Player &player) :
    id(new int(id)),
    name(new std::string(name)),
    x(new int(x)),
    y(new int(y)),
    occupyingArmies(new int(numberOfTerritories)),
    ownedBy(&player)
{
}

Territory::Territory(const Territory &territory) :
    id(new int(*territory.id)),
    name(new std::string(*territory.name)),
    x(new int(*territory.x)),
    y(new int(*territory.y)),
    occupyingArmies(new int(*territory.occupyingArmies)),
    ownedBy(territory.ownedBy)
{
}

Territory::~Territory()
{
    // Non-owning pointer ownedBy is not deleted
    delete this->id;
    delete this->name;
    delete this->x;
    delete this->y;
    delete this->occupyingArmies;
}

void Territory::setOwningPlayer(const Player &player)
{
    this->ownedBy = &player;
}

void Territory::unsetOwningPlayer()
{
    this->ownedBy = nullptr;
}

const Player *Territory::getOwningPlayer() const
{
    return this->ownedBy;
}

Territory &Territory::operator=(const Territory &territory)
{
    if (&territory == this)
    {
        return *this;
    }

    *this->id = *territory.id;
    *this->name = *territory.name;
    *this->x = *territory.x;
    *this->y = *territory.y;
    *this->occupyingArmies = *territory.occupyingArmies;
    this->ownedBy = territory.ownedBy;
    return *this;
}

bool Territory::operator==(const Territory &territory) const
{
    return (*this->id == *territory.id && *this->name == *territory.name);
}

bool Territory::operator!=(const Territory &territory) const
{
    return !(*this == territory);
}

void Territory::setId(int *id)
{
    Territory::id = id;
}

int Territory::getId() const
{
    return *this->id;
}

int Territory::getOccupyingArmies() const
{
    return *this->occupyingArmies;
}

const std::string &Territory::getName() const
{
    return *this->name;
}

void Territory::setName(std::string &name)
{
    *this->name = name;
}

void Territory::setOccupyingArmies(int occupyingArmies)
{
    if (occupyingArmies >= 0)
    {
        *(this->occupyingArmies) = occupyingArmies;
    }
    else
    {
        std::cout << "Cannot assign negative value to number of armies." << std::endl;
    }
}

void Territory::addArmies(int armies)
{
    if (*this->occupyingArmies + armies < 0)
    {
        std::cout << "Current armies: " << this->occupyingArmies
                  << ", attempting to add " << armies << " produces a negative value"
                  << std::endl;
        return;
    }

    *this->occupyingArmies += armies;
}

std::ostream &operator<<(std::ostream &output, const Territory &territory)
{
    output << "Territory (id: " << *territory.id << ", name: " << *territory.name
           << ", armies:" << *territory.occupyingArmies;
    if (territory.ownedBy != nullptr)
    {
        output << ", owning player: (" << territory.ownedBy << ") "
               << *territory.ownedBy;
    }
    else
    {
        output << ", owning player: "
               << "None";
    }

    output << ")\n";
    return output;
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Continent
//============================================================================================================================================================

Continent::Continent(const std::string &name, int armyValue, const std::string &color) :
    name(new std::string(name)),
    armyValue(new int(armyValue)),
    color(new std::string(color)),
    territories(new Graph<Territory>())
{
}

Continent::Continent(const Continent &continent) :
    name(new std::string(*continent.name)),
    armyValue(new int(*continent.armyValue)),
    color(new std::string(*continent.color)),
    territories(new Graph<Territory>(*continent.territories))
{
}

Continent::~Continent()
{
    delete this->name;
    delete this->armyValue;
    delete this->color;
    delete this->territories;
}

Continent &Continent::operator=(const Continent &continent)
{
    if (&continent == this)
    {
        return *this;
    }

    *this->name = *continent.name;
    *this->territories = *continent.territories;
    *this->armyValue = *continent.armyValue;
    *this->color = *continent.color;
    return *this;
}

const std::string &Continent::getName() const
{
    return *name;
}

bool Continent::isValidContinent(const Graph<Territory> &territories) const
{
    return this->territories->isSubgraphOf(territories);
}

void Continent::connectTerritories(const Territory &territory1,
                                   const Territory &territory2)
{
    this->territories->connect(territory1, territory2);
}

void Continent::addTerritory(const Territory &territory)
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

std::ostream &operator<<(std::ostream &output, const Continent &continent)
{
    output << "\nName: " << *continent.name << "\n";
    output << "Color: " << *continent.color << "\n";
    output << "Army Value: " << *continent.armyValue << "\n";
    output << "Territories: \n";
    for (auto &entry : continent.getTerritories())
    {
        output << entry;
    }
    return output;
}

std::unordered_set<Territory> Continent::getTerritories() const
{
    return this->territories->getVertices();
}

int Continent::getBonusArmyValue() const
{
    return *this->armyValue;
}

void Continent::updateTerritory(const Territory &current, const Territory &replacement)
{
    this->territories->update(current, replacement);
}

void Continent::setTerritoryOwner(const Territory &territory, const Player &owner)
{
    const Territory *t = this->territories->findIf(
        [territory](const Territory &t) { return t == territory; });

    if (t != nullptr)
    {
        Territory replacement = *t;
        replacement.setOwningPlayer(owner);
        this->updateTerritory(*t, replacement);
    }
}

//============================================================================================================================================================
// CLASS DEFINITIONS: Map
//============================================================================================================================================================

Map::Map() :
    territories(new Graph<Territory>()), continents(new std::vector<Continent>())
{
}

Map::Map(const Map &map) :
    Subject(),
    territories(new Graph<Territory>(*map.territories)),
    continents(new std::vector<Continent>(*map.continents))
{
}

Map::~Map()
{
    delete territories;
    delete continents;
}

Map &Map::operator=(const Map &map)
{
    *this->territories = *map.territories;
    *this->continents = *map.continents;
    return *this;
}

const Graph<Territory> &Map::getTerritories() const
{
    return *territories;
}

const std::vector<Continent> &Map::getContinents() const
{
    return *continents;
}

const std::unordered_set<Territory> *Map::getNeighbors(const Territory &t) const
{
    return this->territories->getNeighbors(t);
}

std::unordered_set<Territory> Map::getCommonOwnerNeighbors(const Territory &t) const
{
    if (t.getOwningPlayer() == nullptr)
    {
        return std::unordered_set<Territory>();
    }

    const std::unordered_set<Territory> *neighbors = this->getNeighbors(t);
    std::vector<Territory> playerOwnedList = this->getPlayersTerritories(*t.getOwningPlayer());
    std::unordered_set<Territory> playerOwned(playerOwnedList.begin(), playerOwnedList.end());
    return SetUtilities::setIntersect(*neighbors, playerOwned);
}

std::unordered_set<Territory> Map::getDisjunctOwnerNeighbors(const Territory &t) const
{
    if (t.getOwningPlayer() == nullptr)
    {
        return std::unordered_set<Territory>();
    }

    const std::unordered_set<Territory> *neighbors = this->getNeighbors(t);
    std::vector<Territory> playerOwnedList = this->getPlayersTerritories(*t.getOwningPlayer());
    std::unordered_set<Territory> playerOwned(playerOwnedList.begin(), playerOwnedList.end());
    return SetUtilities::setDifference(*neighbors, playerOwned);
}


MapState Map::validate() const
{
    if (!this->territories->isConnected())
    {
        return MapState::NOT_CONNECTED_GRAPH;
    }

    // To check that continents are connected subgraphs:
    // Merge all nodes for each continent into a single node (maintaining edges)
    // if the resulting graph is connected, then continents are connected subgraphs
    Graph<Territory> continentGraph = *this->territories;
    for (const Continent &continent : *this->continents)
    {
        // We collapse it down to the first node
        auto it = continent.begin();
        if (it == continent.end())
        {
            continue;
        }

        for (auto nextIt = it + 1; nextIt != continent.end(); ++nextIt)
        {
            continentGraph.merge(*it, *nextIt);
        }
    }

    if (!continentGraph.isConnected())
    {
        return MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS;
    }

    // Second check to make sure each continent is a subgraph of the world
    for (const Continent &continent : *this->continents)
    {
        if (!continent.isValidContinent(*this->territories))
        {
            return MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS;
        }
    }

    // Scan through territories via continents and flag the error when a territory is
    // seen twice Assure each territory is in one and only one continent
    std::unordered_set<Territory> territories;
    for (const Continent &continent : *this->continents)
    {
        for (const Territory &territory : continent.getTerritories())
        {
            if (territories.count(territory) == 0)
            {
                territories.insert(territory);
            }
            else
            {
                return MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET;
            }
        }
    }

    // Check for a territory that is not part of a continent
    for (const Territory &territory : *this->territories)
    {
        if (territories.count(territory) == 0)
        {
            return MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET;
        }
    }

    return MapState::VALID;
}

Graph<Territory> &Map::getGraph()
{
    return *this->territories;
}

std::vector<Continent> &Map::getContinents()
{
    return *this->continents;
}

std::string Map::getErrorString(MapState mapState) const
{
    switch (mapState)
    {
    case MapState::VALID:
        return "Map contains no errors";
    case MapState::NOT_CONNECTED_GRAPH:
        return "Map is not a connected graph";
    case MapState::CONTINENTS_NOT_CONNECTED_SUBGRAPHS:
        return "Map continents are not all connected subgraphs of the territories";
    case MapState::TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET:
        return "Some map territories do not belong to only one continent";
    default:
        return "Invalid MapState Error code";
    }
}

void Map::addContinent(const Continent &continent)
{
    this->continents->push_back(continent);
}

void Map::addTerritory(const Territory &territory, int continentId)
{
    std::cout << "Adding territory: " << territory << std::endl;
    if (continentId <= 0 ||
        static_cast<std::size_t>(continentId) > this->continents->size())
    {
        std::cout << "Invalid continent id" << std::endl;
    }

    this->territories->insert(territory);
    this->continents->at(continentId - 1).addTerritory(territory);
}

void Map::connectTerritories(int territoryId1, int territoryId2)
{
    auto findTerritory1 = [territoryId1](const Territory &t) {
        return t.getId() == territoryId1;
    };
    auto findTerritory2 = [territoryId2](const Territory &t) {
        return t.getId() == territoryId2;
    };
    const Territory *territory1 = this->territories->findIf(findTerritory1);
    const Territory *territory2 = this->territories->findIf(findTerritory2);
    if (territory1 == nullptr || territory2 == nullptr)
    {
        // These territories do not yet exist
        return;
    }

    this->territories->connect(*territory1, *territory2);
    for (Continent &continent : *this->continents)
    {
        continent.connectTerritories(*territory1, *territory2);
    }
}

std::vector<Territory> Map::getPlayersTerritories(const Player &player) const
{
    std::vector<Territory> ownedTerritories;
    for (const auto &territory : *this->territories)
    {
        if (territory.getOwningPlayer() != nullptr &&
            *territory.getOwningPlayer() == player)
        {
            ownedTerritories.push_back(territory);
        }
    }
    return ownedTerritories;
}

std::vector<Territory> Map::getPlayersTerritoriesNonConst(const Player &player)
{
    std::vector<Territory> ownedTerritories;
    for (const auto &territory : *this->territories)
    {
        if (territory.getOwningPlayer() != nullptr &&
            *territory.getOwningPlayer() == player)
        {
            ownedTerritories.push_back(territory);
        }
    }
    return ownedTerritories;
}

std::vector<Continent> Map::getPlayersContinents(const Player &player) const
{
    std::vector<Continent> ownedContinents;
    for (const auto &continent : *this->continents)
    {
        bool hasFullOwnership = true;
        for (const auto &territory : continent.getTerritories())
        {
            if (territory.getOwningPlayer() != nullptr &&
                *territory.getOwningPlayer() != player)
            {
                hasFullOwnership = false;
            }
        }

        if (hasFullOwnership)
        {
            ownedContinents.push_back(continent);
        }
    }
    return ownedContinents;
}

void Map::setTerritoryOwnerByName(Player &player, const std::string &territoryName)
{
    const Territory *t = this->territories->findIf(
        [territoryName](const Territory &t) { return t.getName() == territoryName; });

    if (t == nullptr)
    {
        return;
    }
    Territory replacement = *t;
    replacement.setOwningPlayer(player);
    this->updateTerritory(*t, replacement);
}

void Map::updateTerritory(const Territory &current, const Territory &replacement)
{
    // copy the current vertex
    Territory copy = current;

    this->territories->update(copy, replacement);
    for (auto &continent : *this->continents)
    {
        continent.updateTerritory(copy, replacement);
    }
}

void Map::setTerritoryOwner(const Territory &territory, const Player &owner)
{
    const Territory *t = this->territories->findIf(
        [territory](const Territory &t) { return t == territory; });
    Territory copy = *t;

    if (t != nullptr)
    {
        Territory replacement = *t;
        replacement.setOwningPlayer(owner);
        this->updateTerritory(copy, replacement);
    }

    for (auto &continent : *this->continents)
    {
        continent.setTerritoryOwner(copy, owner);
    }
}

std::ostream &operator<<(std::ostream &output, const Map &map)
{
    for (auto &entry : *map.continents)
    {
        output << entry;
    }
    return output;
}

std::size_t Map::size() const
{
    return this->territories->size();
}

int Map::getContinentIdByName(const std::string &name){
    int i = 1;
    for (const auto& continent : *this->continents){
        if (name == continent.getName())
            break;
        i++;
    }
    return i;
}

int Map::getTerritoryIdByName(const std::string &name){
    for (const auto& territory : this->territories->getVertices()){
        if (name == territory.getName())
            return territory.getId();
    }
    return -1;
}

const Territory *Map::getTerritory(const Territory &t)
{
    return this->territories->findIf([&t](const Territory &territory){ return t == territory; });
}