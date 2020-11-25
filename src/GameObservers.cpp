#include "GameObservers.h"
#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include <iomanip>
#include <set>
#include <unordered_map>

Observer::Observer()
{
}

Observer::~Observer()
{
}

Subject::Subject() :
    observers(new std::vector<Observer*>())
{
}

Subject::~Subject()
{
    delete observers;
}

void Subject::attach(Observer *o)
{
    observers->push_back(o);
}

void Subject::detach(Observer *o)
{
    auto it = std::find(this->observers->begin(), this->observers->end(), o);
    if (it != this->observers->end())
    {
        this->observers->erase(it);
    }
}

void Subject::notify()
{
    for (auto* observer : *this->observers)
    {
        observer->update();
    }
}

StatisticsObserver::StatisticsObserver(GameEngine& game) :
    game(&game)
{
    game.attach(this);
}

void StatisticsObserver::update() const
{
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Statistics View" << std::endl;
    if (this->game->gameShouldEnd())
    {
        this->displayVictory();
    }
    else
    {
        this->displayPlayers();
        std::cout << std::endl;
        this->displayTopDeployed();
        std::cout << std::endl;
        this->displayTopReinforced();
    }
    std::cout << std::endl;
}

void StatisticsObserver::displayPlayers() const
{
    std::cout << std::setw(SMALL_COLUMN) << std::left << "Player" << "| " << std::setw(MED_COLUMN) << std::left << "# Territories" << "| " << std::setw(MED_COLUMN) << std::left << "% Territories" << "|" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    for (const auto& player : this->game->getPlayers())
    {
        std::cout << std::setw(SMALL_COLUMN) << std::left << player.getPlayerName() << "| " << std::setw(MED_COLUMN) << std::left << this->game->getMap().getPlayersTerritories(player).size() << "| " << std::setw(MED_COLUMN) << std::left << static_cast<float>(this->game->getMap().getPlayersTerritories(player).size()) / this->game->getMap().size() << "|" << std::endl;
    }
    std::cout << "-------------------------------------------------------" << std::endl;
}

void StatisticsObserver::displayTopDeployed() const
{
    const std::vector<Player>& players = this->game->getPlayers();
    if (players.size() == 0)
    {
        return;
    }

    Player top;
    int maxDeployed = -1;
    for (const auto& player : players)
    {
        int playerDeployed = 0;
        for (const auto& territory : this->game->getMap().getPlayersTerritories(player))
        {
            playerDeployed += territory.getOccupyingArmies();
        }

        if (playerDeployed > maxDeployed)
        {
            top = player;
            maxDeployed = playerDeployed;
        }
    }

    std::cout << "Most deployed armies: " << top.getPlayerName() << " with " << maxDeployed << std::endl;
}

void StatisticsObserver::displayTopReinforced() const
{
    const std::vector<Player>& players = this->game->getPlayers();
    if (players.size() == 0)
    {
        return;
    }

    Player top;
    int maxReinforced = -1;
    for (const auto& player : players)
    {
        int reinforced = GameLogic::totalArmyBonus(this->game->getMap(), player);
        if (reinforced > maxReinforced)
        {
            top = player;
            maxReinforced = reinforced;
        }
    }

    std::cout << "Most reinforcements per turn: " << top.getPlayerName() << " with " << maxReinforced << std::endl;
}

void StatisticsObserver::displayVictory() const
{
    if (this->game->getPlayers().size() == 0)
    {
        return;
    }

    // There will only be one player left
    std::cout << this->game->getPlayers().at(0).getPlayerName() << " has conquered the world!" << std::endl;
    std::cout << std::endl;
    std::cout << VICTORY_BANNER << std::endl;
}

PhaseObserver::PhaseObserver(GameEngine& game) :
    game(&game)
{
    game.attach(this);
}

void PhaseObserver::update() const
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Phase View: ";
    switch (this->game->getCurrentPhase())
    {
    case GamePhase::REINFORCEMENT:
        this->displayReinforcementsPhase();
        break;
    case GamePhase::ISSUE_ORDERS:
        this->displayIssueOrdersPhase();
        break;
    case GamePhase::EXECUTE_ORDERS:
        this->displayOrdersExecutionPhase();
        break;
    }
}

void PhaseObserver::displayReinforcementsPhase() const
{
    const Player& player = this->game->getCurrentPlayer();
    std::cout << "Reinforcement Phase" << std::endl;
    std::cout << "Player: " << player.getPlayerName() << std::endl;

    const auto& territories = this->game->getMap().getPlayersTerritories(player);
    const auto& continents = this->game->getMap().getPlayersContinents(player);
    std::cout << "You currently own " << territories.size() << " territories." << std::endl;
    for (const auto& territory : territories)
    {
        std::cout << territory.getName() << " with " << territory.getOccupyingArmies() << " armies." << std::endl;
    }

    std::cout << "You currently own " << continents.size() << " continents." << std::endl;
    for (const auto& continent : continents)
    {
        std::cout << continent.getName() << " with " << continent.getBonusArmyValue() << " bonus armies." << std::endl;
    }
    std::cout << "Total territory control reinforcements: " << GameLogic::territoryArmyBonus(this->game->getMap(), player) << std::endl;
    std::cout << "Total continent control reinforcements: " << GameLogic::continentArmyBonus(this->game->getMap(), player) << std::endl;
    std::cout << "Total reinforcements this turn: " << GameLogic::totalArmyBonus(this->game->getMap(), player) << std::endl;
}

void PhaseObserver::displayIssueOrdersPhase() const
{
    const Player& player = this->game->getCurrentPlayer();
    std::cout << "Issue Orders Phase" << std::endl;
    std::cout << "Player: " << player.getPlayerName() << std::endl;

    std::cout << "Current orders: " << std::endl;
    for (const auto* order : player.getOrders().getList())
    {
        std::cout << order << std::endl;
    }

    std::cout << "Current territories to attack: ";
    for (const auto& territory : player.toAttack(this->game->getMap()))
    {
        std::cout << territory.getName() << ", ";
    }
    std::cout << std::endl;

    std::cout << "Current territories to defend: ";
    for (const auto& territory : player.toDefend(this->game->getMap()))
    {
        std::cout << territory.getName() << ", ";
    }
    std::cout << std::endl;
}

void PhaseObserver::displayOrdersExecutionPhase() const
{
    const Player& player = this->game->getCurrentPlayer();
    std::cout << "Execute Orders Phase" << std::endl;
    std::cout << "Player: " << player.getPlayerName() << std::endl;

    std::cout << "Some or all of your orders have been executed: " << std::endl; 
    for (const auto* order : player.getOrders().getList())
    {
        std::cout << order << std::endl;
    }
}
