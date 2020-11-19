#include "GameEngine.h"

#include <algorithm>
#include <functional>
#include <cmath>

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
    // TODO: Fill
    *this->currentPhase = GamePhase::EXECUTE_ORDERS;
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
