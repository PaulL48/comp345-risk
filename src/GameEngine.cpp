#include "GameEngine.h"

#include <algorithm>
#include <functional>
#include <cmath>
#include <typeindex>

int GameLogic::territoryArmyBonus(const Map& map, const Player& player)
{
    std::vector<Territory> territoriesOwned = map.getPlayersTerritories(player);
    return static_cast<int>(std::floor(territoriesOwned.size() / GameLogic::TERRITORY_TO_ARMY_DIVISOR));
}

int GameLogic::continentArmyBonus(const Map& map, const Player& player)
{
    std::vector<Continent> continentsOwned = map.getPlayersContinents(player);
    int continentBonus = 0;
    for (const auto& continent : continentsOwned)
    {
        continentBonus += continent.getBonusArmyValue();
    }
    return continentBonus;
}

int GameLogic::totalArmyBonus(const Map& map, const Player& player)
{
    return std::max(GameLogic::territoryArmyBonus(map, player) + GameLogic::continentArmyBonus(map, player), GameLogic::MINIMUM_REINFORCEMENTS_PER_TURN);
}

int GameLogic::playerTotalAvailableArmies(const Map& map, const Player& player)
{
    std::vector<Territory> territories = map.getPlayersTerritories(player);
    int deployedArmies = 0;
    for (const auto& territory : territories)
    {
        deployedArmies += territory.getOccupyingArmies();
    }
    return deployedArmies + player.getReinforcementPool();
}

bool GameLogic::playerIsDefeated(const Map& map, const Player& player)
{
    return map.getPlayersTerritories(player).size() == 0;
}

void addNextPhasedOrderOrNothing(std::vector<Order*>& masterList, const std::vector<Order*>& playerList, std::vector<Order*>::const_iterator& cursor,  const std::vector<std::type_index>& selectedTypes)
{
    for (; cursor != playerList.end(); ++cursor)
    {
        if (std::find(selectedTypes.begin(), selectedTypes.end(), std::type_index(typeid(*cursor))) != selectedTypes.end())
        {
            masterList.push_back(*cursor);
            return;
        }
    }
}

void fillRoundRobinOrders(std::vector<Order*>& masterList, std::vector<Player>& players, const std::vector<std::type_index>& selectedTypes)
{
    std::vector<std::vector<Order*>::const_iterator> cursors;
    for (auto& player : players)
    {
        cursors.push_back(player.getOrders().getList().begin());
    }

    bool allListsScanned = false;
    while (!allListsScanned)
    {
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            addNextPhasedOrderOrNothing(masterList, players.at(i).getOrders().getList(), cursors.at(i), selectedTypes);
        }

        allListsScanned = true;
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            allListsScanned &= cursors.at(i) == players.at(i).getOrders().getList().end();
        }
    }
}

GameEngine::GameEngine(const Map& map, const std::vector<Player>& players) : 
    map(new Map(map)), 
    players(new std::vector<Player>(players)), 
    currentPhase(new GamePhase()), 
    currentPlayer(new std::size_t())
{}

void GameEngine::mainGameLoop()
{
    while (!gameShouldEnd())
    {
        for (std::size_t i = 0; i < this->players->size(); ++i)
        {
            *this->currentPlayer = i;
            this->reinforcementPhase(this->players->at(i));
            this->issueOrdersPhase(this->players->at(i));
        }
        this->executeOrdersPhase();
        cullDefeatedPlayers();
    }
}

void GameEngine::reinforcementPhase(Player& player)
{
    *this->currentPhase = GamePhase::REINFORCEMENT;
    player.addArmies(GameLogic::totalArmyBonus(*this->map, player));
}

void GameEngine::issueOrdersPhase(Player& player)
{
    *this->currentPhase = GamePhase::ISSUE_ORDERS;
    player.issueOrder(*this->map);
}

void GameEngine::executeOrdersPhase()
{
    *this->currentPhase = GamePhase::EXECUTE_ORDERS;
    // TODO: Notify observer

    this->players->at(0).getOrders();

    std::vector<Order*> masterList;
    std::vector<std::type_index> deployPriority;
    Fill<Deploy>(deployPriority);
    fillRoundRobinOrders(masterList, *this->players, deployPriority);

    std::vector<std::type_index> airliftPriority;
    Fill<Airlift>(airliftPriority);
    fillRoundRobinOrders(masterList, *this->players, airliftPriority);

    std::vector<std::type_index> blockadePriority;
    Fill<Blockade>(blockadePriority);
    fillRoundRobinOrders(masterList, *this->players, blockadePriority);

    std::vector<std::type_index> remainingPriorities;
    Fill<Advance, Bomb, Airlift, Negotiate>(remainingPriorities);
    fillRoundRobinOrders(masterList, *this->players, remainingPriorities);

    for (Order* order : masterList)
    {
        // TODO: Print some stuff so the TA sees all deploys are executed first
        order->execute();
    }
}

const Player& GameEngine::getCurrentPlayer() const
{
    return this->players->at(*this->currentPlayer);
}

std::vector<Territory> GameEngine::getCurrentPlayerOwnedTerritories() const
{
    return this->map->getPlayersTerritories(this->getCurrentPlayer());
}

std::vector<Continent> GameEngine::getCurrentPlayerOwnedContinents() const
{
    return this->map->getPlayersContinents(this->getCurrentPlayer());
}

int GameEngine::getCurrentPlayerOwnedContinentControlBonus() const
{
    return GameLogic::continentArmyBonus(*this->map, this->getCurrentPlayer());
}

int GameEngine::getCurrentPlayerTotalAvailableArmies() const
{
    return GameLogic::playerTotalAvailableArmies(*this->map, this->getCurrentPlayer());
}

GamePhase GameEngine::getCurrentPhase() const
{
    return *this->currentPhase;
}

bool GameEngine::gameShouldEnd() const
{
    // If a player owns all the territories and defeated players are culled, 
    // only one player will remain
    return this->players->size() == 1;
}

void GameEngine::cullDefeatedPlayers()
{
    auto predicate = [this](const Player& p) { return GameLogic::playerIsDefeated(*map, p); };
    auto it = std::remove_if(this->players->begin(), this->players->end(), predicate);
    if (it != this->players->end())
    {
        this->players->erase(it);
    }
}
