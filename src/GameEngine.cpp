#include "GameEngine.h"

#include "Cards.h"
#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <typeindex>
#include <vector>

std::ostream &operator<<(std::ostream &output, const GamePhase& gamePhase)
{
    switch (gamePhase)
    {
    case GamePhase::REINFORCEMENT:
        output << "Reinforcement";
        break;
    case GamePhase::ISSUE_ORDERS:
        output << "Issue orders";
        break;
    case GamePhase::EXECUTE_ORDERS:
        output << "Reinforcement";
        break;
    }
    return output;
}

std::vector<Player> ConfigurationUtilities::getPlayers()
{
    std::cout << "---------------------------------------------------------------"
              << std::endl;
    std::size_t value = InputUtilities::getRangedInput(
        "Please select the number of players in your game", 2, 5);
    std::cout << "---------------------------------------------------------------"
              << std::endl;
    std::cout << std::endl;

    std::vector<Player> players(value);
    ConfigurationUtilities::getPlayerNames(players);
    ConfigurationUtilities::getPlayerStrategies(players);
    return players;
}

void ConfigurationUtilities::getPlayerNames(std::vector<Player> &players)
{
    std::unordered_set<std::string> usedNames;
    std::size_t i = 0;
    for (auto &player : players)
    {
        std::string name;
        while (name.empty() || usedNames.count(name) != 0)
        {
            std::cout << "Player " << i + 1 << " set your name: ";
            std::getline(std::cin, name);
            InputUtilities::removeNewlines(name);
            if (name.empty())
            {
                std::cout << "No input" << std::endl;
            }

            if (usedNames.count(name) != 0)
            {
                std::cout << "Name is already taken" << std::endl;
            }
        }
        player.setPlayerName(name);
        usedNames.insert(name);
        ++i;
    }
}

void ConfigurationUtilities::getPlayerStrategies(std::vector<Player> &players)
{
    for (auto &player : players)
    {
        std::size_t choice = InputUtilities::getNumericalMenuChoice(
            "Select a strategy for " + player.getPlayerName(),
            std::vector<std::string>{"Human", "Aggressive", "Benevolent", "Neutral"});
        switch (choice)
        {
        case 0:
            player.setStrategy(HumanPlayerStrategy());
            break;
        case 1:
            player.setStrategy(AggressivePlayerStrategy());
            break;
        case 2:
            player.setStrategy(BenevolentPlayerStrategy());
            break;
        case 3:
            player.setStrategy(NeutralPlayerStrategy());
            break;
        }
    }
}

Map ConfigurationUtilities::getMap()
{
    std::vector<std::string> maps;
    for (auto &directoryEntry : std::filesystem::directory_iterator("./maps"))
    {
        std::string fileName = directoryEntry.path().string();
        maps.push_back(fileName);
    }

    bool valid = false;
    Map m;
    while (!valid)
    {
        std::string choice = InputUtilities::getMenuChoice(
            "Map Selection. Please choose from the following maps: ", maps);
        m = MapReader().read(choice, valid);
        std::cout << "Checking map integrity" << std::endl;
        MapState state = m.validate();
        if (state != MapState::VALID)
        {
            std::cout << "Map structure error: " << m.getErrorString(state)
                      << std::endl;
        }
        else
        {
            std::cout << "Map integrity good" << std::endl;
        }
    }
    std::cout << "Map contents: " << std::endl;
    std::cout << m << std::endl;
    return m;
}

bool ConfigurationUtilities::getPhaseObserverSwitch()
{
    std::cout << "---------------------------------------------------------------"
              << std::endl;
    std::size_t choice = InputUtilities::getNumericalMenuChoice(
        "Please select if you want the Phase observers ON or OFF",
        std::vector<std::string>{"Phase observers ON", "Phase observers OFF"});
    return choice == 0;
}

bool ConfigurationUtilities::getStatisticsObserverSwitch()
{
    std::cout << "---------------------------------------------------------------"
              << std::endl;
    std::size_t choice = InputUtilities::getNumericalMenuChoice(
        "Please select if you want the Game Statistic Observers ON or OFF",
        std::vector<std::string>{"Game Statistic Observers ON",
                                 "Game Statistic Observers OFF"});
    return choice == 0;
}

void StartupUtilities::shufflePlayers(std::vector<Player> &players)
{
    std::cout << "Randomizing player order." << std::endl;
    auto rd = std::random_device();
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(players), std::end(players), rng);

    std::cout << "Randomized order is: " << std::endl;
    for (const auto &player : players)
    {
        std::cout << player << std::endl;
    }
}

int StartupUtilities::startingArmies(int playerCount)
{
    switch (playerCount)
    {
    case 2:
        return 40;
    case 3:
        return 35;
    case 4:
        return 30;
    case 5:
        return 25;
    default:
        return 0;
    }
}

void StartupUtilities::assignStartingArmies(std::vector<Player> &players)
{
    int startingArmies = StartupUtilities::startingArmies(players.size());

    for (auto &player : players)
    {
        std::cout << "Adding " << startingArmies << " armies to player: " << player
                  << std::endl;
        player.addArmies(startingArmies);
        std::cout << "Result" << player << std::endl;
    }
}

void StartupUtilities::playersDrawCards(std::vector<Player> &players, Deck &deck,
                                        int cardsPerHand)
{
    for (auto &player : players)
    {
        std::cout << "Drawing initial cards for player: " << player << std::endl;
        for (int i = 0; i < cardsPerHand; ++i)
        {
            player.getCards().addToHand(deck.draw());
        }
    }
}

void StartupUtilities::assignTerritories(std::vector<Player> &players, Map &map)
{
    std::cout << "Randomly assigning territories to players" << std::endl;
    Graph<Territory> &territories = map.getGraph();

    std::vector<Territory> shuffledTerritories;
    for (const Territory &territory : territories)
    {
        shuffledTerritories.push_back(territory);
    }
    auto rd = std::random_device();
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(shuffledTerritories), std::end(shuffledTerritories), rng);
    std::vector<std::pair<Territory, const Player *>> changes;
    int playerIndex = 0;
    for (const Territory &territory : shuffledTerritories)
    {
        std::cout << "Assinging player (" << &players.at(playerIndex) << ") "
                  << players.at(playerIndex) << std::endl;
        changes.push_back(std::make_pair(territory, &players.at(playerIndex)));
        ++playerIndex;
        playerIndex %= players.size();
    }
    for (auto &[territoryObj, playerObj] : changes)
    {
        std::cout << "Setting ownership: " << std::endl;
        std::cout << territoryObj << " to " << *playerObj << std::endl;
        map.setTerritoryOwner(territoryObj, *playerObj);
    }
}

int GameLogic::territoryArmyBonus(const Map &map, const Player &player)
{
    std::vector<Territory> territoriesOwned = map.getPlayersTerritories(player);
    return static_cast<int>(
        std::floor(territoriesOwned.size() / GameLogic::TERRITORY_TO_ARMY_DIVISOR));
}

int GameLogic::continentArmyBonus(const Map &map, const Player &player)
{
    std::vector<Continent> continentsOwned = map.getPlayersContinents(player);
    int continentBonus = 0;
    for (const auto &continent : continentsOwned)
    {
        continentBonus += continent.getBonusArmyValue();
    }
    return continentBonus;
}

int GameLogic::totalArmyBonus(const Map &map, const Player &player)
{
    return std::max(GameLogic::territoryArmyBonus(map, player) +
                        GameLogic::continentArmyBonus(map, player),
                    GameLogic::MINIMUM_REINFORCEMENTS_PER_TURN);
}

int GameLogic::playerTotalAvailableArmies(const Map &map, const Player &player)
{
    std::vector<Territory> territories = map.getPlayersTerritories(player);
    int deployedArmies = 0;
    for (const auto &territory : territories)
    {
        deployedArmies += territory.getOccupyingArmies();
    }
    return deployedArmies + player.getReinforcementPool();
}

bool GameLogic::playerIsDefeated(const Map &map, const Player &player)
{
    return map.getPlayersTerritories(player).size() == 0;
}

void GameLogic::addCardToConqueringPlayers(std::vector<Player> &players, Deck &deck)
{
    for (auto &player : players)
    {
        if (player.getConqueredTerritory())
        {
            std::cout << "Player: " << player
                      << " is awarded a card for conquering a territory this turn"
                      << std::endl;
            player.getCards().addToHand(deck.draw());
            player.setConqueredTerritory(false);
        }
    }
}

void GameLogic::fillRoundRobinOrders(std::vector<Order *> &masterList,
                                     const std::vector<Player> &players,
                                     int executionPriority)
{
    std::vector<std::vector<Order *>::const_iterator> cursors;
    for (auto &player : players)
    {
        cursors.push_back(player.getOrders().getList().begin());
    }

    bool allListsScanned = false;
    while (!allListsScanned)
    {
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            GameLogic::addExecutionPriorityOrderToMaster(
                masterList, players.at(i).getOrders().getList(), cursors.at(i),
                executionPriority);
        }

        allListsScanned = true;
        for (std::size_t i = 0; i < cursors.size(); ++i)
        {
            allListsScanned &=
                cursors.at(i) == players.at(i).getOrders().getList().end();
        }
    }
}

void GameLogic::addExecutionPriorityOrderToMaster(
    std::vector<Order *> &masterList, const std::vector<Order *> &playerOrders,
    std::vector<Order *>::const_iterator &cursor, int executionPriority)
{
    for (; cursor != playerOrders.end(); ++cursor)
    {
        if ((*cursor)->getExecutionPriority() == executionPriority)
        {
            masterList.push_back(*cursor);
            ++cursor;
            return;
        }
    }
}

std::vector<Order *>
GameLogic::constructMasterExecutionList(const std::vector<Player> &players)
{
    std::vector<Order *> masterList;
    GameLogic::fillRoundRobinOrders(masterList, players, DEPLOY_PRIORITY);
    GameLogic::fillRoundRobinOrders(masterList, players, AIRLIFT_PRIORITY);
    GameLogic::fillRoundRobinOrders(masterList, players, BLOCKADE_PRIORITY);
    GameLogic::fillRoundRobinOrders(masterList, players, REMAINDER_PRIORITY);
    return masterList;
}

GameEngine::GameEngine() :
    phaseObserver(new bool(false)),
    stateObserver(new bool(false)),
    map(new Map()),
    players(new std::vector<Player>()),
    currentPhase(new GamePhase()),
    currentPlayer(new std::size_t()),
    deck(new Deck())
{
}

GameEngine::GameEngine(const GameEngine &game) :
    Subject(),
    phaseObserver(new bool(*game.phaseObserver)),
    stateObserver(new bool(*game.stateObserver)),
    map(new Map(*game.map)),
    players(new std::vector<Player>(*game.players)),
    currentPhase(new GamePhase(*game.currentPhase)),
    currentPlayer(new std::size_t(*game.currentPlayer)),
    deck(new Deck(*game.deck))
{
}

GameEngine &GameEngine::operator=(const GameEngine &gameEngine)
{
    if (this == &gameEngine)
    {
        return *this;
    }

    *this->phaseObserver = *gameEngine.phaseObserver;
    *this->stateObserver = *gameEngine.stateObserver;
    *this->map = *gameEngine.map;
    *this->players = *gameEngine.players;
    *this->currentPhase = *gameEngine.currentPhase;
    *this->currentPlayer = *gameEngine.currentPlayer;
    *this->deck = *gameEngine.deck;
    return *this;
}

std::ostream &operator<<(std::ostream &output, const GameEngine &gameEngine)
{
    output << "Phase observer: " << *gameEngine.phaseObserver
           << "Statistics observer: " << *gameEngine.stateObserver
           << "Map: " << *gameEngine.map
           << "Players: " << *gameEngine.players
           << "Current phase: " << *gameEngine.currentPhase
           << "Current player: " << gameEngine.getCurrentPlayer()
           << "Deck: " << *gameEngine.deck;
    return output;
}

void GameEngine::configure()
{
    *this->phaseObserver = ConfigurationUtilities::getPhaseObserverSwitch();
    *this->stateObserver = ConfigurationUtilities::getStatisticsObserverSwitch();
    *this->players = ConfigurationUtilities::getPlayers();
    *this->map = ConfigurationUtilities::getMap();

    for (auto &player : *this->players)
    {
        player.setGameEngine(this);
    }

    if (*this->stateObserver)
    {
        new StatisticsObserver(*this);
    }

    if (*this->phaseObserver)
    {
        new PhaseObserver(*this);
    }

    std::cout << "====================================================================="
                 "==========="
              << std::endl;
    std::cout << "Game Configuration Phase Complete. Configured settings: "
              << std::endl;
    std::cout << "Phase observer on? " << *this->phaseObserver << std::endl;
    std::cout << "Statistics observer on? " << *this->stateObserver << std::endl;
    std::cout << this->players->size() << " Players participating: " << std::endl;
    for (const auto &player : *this->players)
    {
        std::cout << player << std::endl;
    }
    std::cout << "Selected Map: " << std::endl;
    std::cout << *this->map << std::endl;
    std::cout << "====================================================================="
                 "==========="
              << std::endl;
    std::cout << "Press any enter to continue" << std::endl;
    std::string wait;
    std::getline(std::cin, wait);
}

void GameEngine::startupPhase()
{
    StartupUtilities::assignStartingArmies(*this->players);
    StartupUtilities::shufflePlayers(*this->players);
    StartupUtilities::assignTerritories(*this->players, *this->map);
    StartupUtilities::playersDrawCards(*this->players, *this->deck, 8);

    std::cout << "====================================================================="
                 "==========="
              << std::endl;
    std::cout << "Game Start Phase Complete. Game details: " << std::endl;
    std::cout << "Player order, armies and starting hands: " << std::endl;
    for (const auto &player : *this->players)
    {
        std::cout << player << std::endl;
    }
    std::cout << "Map distribution: " << std::endl;
    std::cout << *this->map << std::endl;
    std::cout << "====================================================================="
                 "==========="
              << std::endl;
    std::cout << "Press any enter to continue" << std::endl;
    std::string wait;
    std::getline(std::cin, wait);
}

void GameEngine::mainGameLoop()
{
    while (!gameShouldEnd())
    {
        this->chooseNewStrategy();
        this->reinforcementPhase();
        this->issueOrdersPhase();
        this->executeOrdersPhase();
        cullDefeatedPlayers();
        GameLogic::addCardToConqueringPlayers(*this->players, *this->deck);
        
        // Flush orders
        for (auto& player : *this->players)
        {
            player.getOrders().clear();
        }
    }
    this->notify();
}

void GameEngine::reinforcementPhase()
{
    *this->currentPhase = GamePhase::REINFORCEMENT;
    std::size_t i = 0;
    for (auto &player : *this->players)
    {
        *this->currentPlayer = i++;
        player.addArmies(GameLogic::totalArmyBonus(*this->map, player));
        this->notify();
    }
}

void GameEngine::issueOrdersPhase()
{
    *this->currentPhase = GamePhase::ISSUE_ORDERS;
    for (std::size_t i = 0; i < this->players->size(); ++i)
    {
        *this->currentPlayer = i;
        this->notify();
        this->players->at(i).issueOrder(*this->map);
        this->notify();
    }
}

void GameEngine::executeOrdersPhase()
{
    *this->currentPhase = GamePhase::EXECUTE_ORDERS;

    std::vector<Order *> masterList =
        GameLogic::constructMasterExecutionList(*this->players);

    for (Order *order : masterList)
    {
        for (std::size_t i = 0; i < this->players->size(); ++i)
        {
            if (this->players->at(i) == *order->getMutableDataPayload().player)
            {
                *this->currentPlayer = i;
            }
        }
        order->execute();
        this->notify();
    }
}

void GameEngine::chooseNewStrategy()
{
    for (auto &player : *this->players)
    {
        std::size_t choice = InputUtilities::getNumericalMenuChoice(player.getPlayerName() + " would you like to change strategies?", std::vector<std::string>{"Yes", "No"});
        if (choice == 0)
        {
            std::cout << "Current strategy is: " << player.getStrategy() << std::endl;
            std::size_t strategyChoice = InputUtilities::getNumericalMenuChoice(
            "Select a new strategy:",
            std::vector<std::string>{"Human", "Aggressive", "Benevolent", "Neutral"});
            switch (strategyChoice)
            {
            case 0:
                player.setStrategy(HumanPlayerStrategy());
                break;
            case 1:
                player.setStrategy(AggressivePlayerStrategy());
                break;
            case 2:
                player.setStrategy(BenevolentPlayerStrategy());
                break;
            case 3:
                player.setStrategy(NeutralPlayerStrategy());
                break;
            }
        }
    }
}

const Player &GameEngine::getCurrentPlayer() const
{
    return this->players->at(*this->currentPlayer);
}

GamePhase GameEngine::getCurrentPhase() const
{
    return *this->currentPhase;
}

const Map &GameEngine::getMap() const
{
    return *this->map;
}

Deck &GameEngine::getDeck()
{
    return *this->deck;
}

const std::vector<Player> &GameEngine::getPlayers() const
{
    return *this->players;
}

bool GameEngine::gameShouldEnd() const
{
    // If a player owns all the territories and defeated players are culled,
    // only one player will remain
    return this->players->size() == 1;
}

void GameEngine::cullDefeatedPlayers()
{
    auto predicate = [this](const Player &p) {
        return GameLogic::playerIsDefeated(*map, p);
    };
    auto it = std::remove_if(this->players->begin(), this->players->end(), predicate);
    if (it != this->players->end())
    {
        this->players->erase(it);
    }
}

GameEngine::~GameEngine()
{
}
