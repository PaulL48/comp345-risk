#include "GameEngine.h"

#include <algorithm>
#include <functional>
#include <cmath>
#include <typeindex>
#include <random>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"

std::vector<Player> ConfigurationUtilities::getPlayers()
{
    int totalPlayers;

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::size_t value = InputUtilities::getRangedInput("Please select the number of players in your game", 2, 5);
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    std::vector<Player> players(value);
    ConfigurationUtilities::getPlayerNames(players);
    return players;
}

void ConfigurationUtilities::getPlayerNames(std::vector<Player>& players)
{
    std::unordered_set<std::string> usedNames;
    std::size_t i = 0;
    for (auto& player : players)
    {
        std::string name;
        while (name.empty() || usedNames.count(name) != 0)
        {
            std::cout << "Player " << i + 1<< " set your name: ";
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
        std::string choice = InputUtilities::getMenuChoice("Map Selection. Please choose from the following maps: ", maps);
        m = MapLoader::loadMapValidated(choice, valid);
        std::cout << "Checking map integrity" << std::endl;
        MapState state = m.validate();
        if (state != MapState::VALID)
        {
            std::cout << "Map structure error: " << m.getErrorString(state) << std::endl;
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
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::size_t choice = InputUtilities::getNumericalMenuChoice("Please select if you want the Phase observers ON or OFF", std::vector<std::string>{"1) Phase observers ON", "2) Phase observers OFF"});
    return choice == 1;
}

bool ConfigurationUtilities::getStatisticsObserverSwitch()
{
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::size_t choice = InputUtilities::getNumericalMenuChoice("Please select if you want the Game Statistic Observers ON or OFF", std::vector<std::string>{"1) Game Statistic Observers ON", "2) Game Statistic Observers OFF"});
    return choice == 1;
}

void StartupUtilities::shufflePlayers(std::vector<Player>& players)
{
    std::cout << "Randomizing player order." << std::endl;
    auto rd = std::random_device(); 
    auto rng = std::default_random_engine {rd()};
    std::shuffle(std::begin(players), std::end(players), rng);

    std::cout << "Randomized order is: " << std::endl;
    for (const auto& player : players)
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

void StartupUtilities::assignStartingArmies(std::vector<Player>& players)
{
    int startingArmies = StartupUtilities::startingArmies(players.size());

    for (auto& player : players)
    {   
        std::cout << "Adding " << startingArmies << " armies to player: " << player << std::endl;
        player.addArmies(startingArmies);
        std::cout << "Result" << player << std::endl;
    }
}

void StartupUtilities::playersDrawCards(std::vector<Player>& players, Deck& deck, int cardsPerHand)
{
    for (auto& player : players)
    {
        std::cout << "Drawing initial cards for player: " << player << std::endl;
        for (int i = 0; i < cardsPerHand; ++i)
        {
            player.getCards().addToHand(deck.draw());
        }
    }
}

void StartupUtilities::assignTerritories(std::vector<Player>& players, Map& map)
{
    std::cout << "Randomly assigning territories to players" << std::endl;
    Graph<Territory>& territories = map.getGraph();

    std::vector<Territory> shuffledTerritories;
    for (const Territory& territory : territories)
    {
        shuffledTerritories.push_back(territory);
    }
    auto rd = std::random_device(); 
    auto rng = std::default_random_engine {rd()};
    std::shuffle(std::begin(shuffledTerritories), std::end(shuffledTerritories), rng);
    std::vector<std::pair< Territory , const Player *>> changes;
    int playerIndex = 0;
    for (const Territory& territory : shuffledTerritories)
    {
        std::cout << "Assinging player (" << &players.at(playerIndex) << ") " << players.at(playerIndex) << std::endl;
        changes.push_back(std::make_pair(territory, &players.at(playerIndex)));
        ++playerIndex;
        playerIndex %= players.size();
    }
    for (auto &[territoryObj, playerObj] : changes)
    {
        std::cout << "Setting ownership: "<< std::endl;
        std::cout << territoryObj << " to " << *playerObj << std::endl;
        map.setTerritoryOwner(territoryObj, *playerObj);
    }
}

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

void GameLogic::addCardToConqueringPlayers(std::vector<Player>& players, Deck& deck)
{
    for (auto& player : players)
    {
        if (player.getConqueredTerritory())
        {
            std::cout << "Player: " << player << " is awarded a card for conquering a territory this turn" << std::endl;
            player.getCards().addToHand(deck.draw());
            player.setConqueredTerritory(false);
        }
    }
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

void GameEngine::configure()
{
    *this->phaseObserver = ConfigurationUtilities::getPhaseObserverSwitch();
    *this->stateObserver = ConfigurationUtilities::getStatisticsObserverSwitch();
    *this->players = ConfigurationUtilities::getPlayers();
    *this->map = ConfigurationUtilities::getMap();

    std::cout << "================================================================================" << std::endl;
    std::cout << "Game Configuration Phase Complete. Configured settings: " << std::endl;
    std::cout << "Phase observer on? " << *this->phaseObserver << std::endl;
    std::cout << "Statistics observer on? " << *this->stateObserver << std::endl;
    std::cout << this->players->size() << " Players participating: " << std::endl;
    for (const auto& player : *this->players)
    {
        std::cout << player << std::endl;
    }
    std::cout << "Selected Map: " << std::endl;
    std::cout << *this->map << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << "Press any enter to continue" << std::endl;
    std::string wait;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, wait);
}

void GameEngine::startupPhase()
{
    StartupUtilities::assignStartingArmies(*this->players);
    StartupUtilities::shufflePlayers(*this->players);
    StartupUtilities::assignTerritories(*this->players, *this->map);
    StartupUtilities::playersDrawCards(*this->players, *this->deck, 1);

    std::cout << "================================================================================" << std::endl;
    std::cout << "Game Start Phase Complete. Game details: " << std::endl;
    std::cout << "Player order, armies and starting hands: " << std::endl;
    for (const auto& player : *this->players)
    {
        std::cout << player << std::endl;
    }
    std::cout << "Map distribution: " << std::endl;
    std::cout << *this->map << std::endl;
    std::cout << "================================================================================" << std::endl;
    std::cout << "Press any enter to continue" << std::endl;
    std::string wait;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, wait);
}

void GameEngine::mainGameLoop()
{
    while (!gameShouldEnd())
    {
        this->reinforcementPhase();
        this->issueOrdersPhase();
        this->executeOrdersPhase();
        cullDefeatedPlayers();
        GameLogic::addCardToConqueringPlayers(*this->players, *this->deck);
    }
}

void GameEngine::reinforcementPhase()
{
    *this->currentPhase = GamePhase::REINFORCEMENT;
    std::cout << "================================================================================" << std::endl;
    std::cout << "Starting Reinforcement Phase" << std::endl;
    std::size_t i = 0;
    for (auto& player : *this->players)
    {
        *this->currentPlayer = i++;
        std::cout << "Reinforcing Player: " << player << std::endl;
        std::cout << "Player owns " << this->map->getPlayersTerritoriesNonConst(player).size() << " territories" << std::endl;
        std::cout << "Player owns " << this->map->getPlayersContinents(player).size() << " continents" << std::endl;
        std::cout << "Adding " << GameLogic::totalArmyBonus(*this->map, player) << " armies to player" << std::endl;
        player.addArmies(GameLogic::totalArmyBonus(*this->map, player));
        std::cout << "Result: " << player << std::endl;
    }
}

void GameEngine::issueOrdersPhase()
{
    *this->currentPhase = GamePhase::ISSUE_ORDERS;

    std::cout << "================================================================================" << std::endl;
    std::cout << "Starting Issue Order Phase" << std::endl;

    for (std::size_t i = 0; i < this->players->size(); ++i)
    {
        *this->currentPlayer = i;
        std::cout << "Current player to issue orders: " << this->players->at(i) << std::endl;
        this->players->at(i).issueOrder(*this->map);
    }
}

void GameEngine::executeOrdersPhase()
{
    *this->currentPhase = GamePhase::EXECUTE_ORDERS;
    // TODO: Notify observer

    std::vector<Order*> masterList;
    std::vector<std::type_index> deployPriority;
    fill<Deploy>(deployPriority);
    fillRoundRobinOrders(masterList, *this->players, deployPriority);

    std::vector<std::type_index> airliftPriority;
    fill<Airlift>(airliftPriority);
    fillRoundRobinOrders(masterList, *this->players, airliftPriority);

    std::vector<std::type_index> blockadePriority;
    fill<Blockade>(blockadePriority);
    fillRoundRobinOrders(masterList, *this->players, blockadePriority);

    std::vector<std::type_index> remainingPriorities;
    fill<Advance, Bomb, Airlift, Negotiate>(remainingPriorities);
    fillRoundRobinOrders(masterList, *this->players, remainingPriorities);

    for (Order* order : masterList)
    {
        order->execute();
    }
}

const Player& GameEngine::getCurrentPlayer() const
{
    return this->players->at(*this->currentPlayer);
}

std::vector<Territory> GameEngine::getCurrentPlayerOwnedTerritories() const
{
    return this->map->getPlayersTerritoriesNonConst(this->players->at(*this->currentPlayer));
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

GameEngine::~GameEngine(){}

// ControlObservers::ControlObservers()
// {
//     std::cout << "---------------------------------------------------------------" << std::endl;
//     std::cout << "Please select if you want the Phase observers ON or OFF" << std::endl; 
//     std::cout << "1) Phase observers ON" << std::endl;
//     std::cout << "2) Phase observers OFF" << std::endl;

//     std::cin >> phaseObserver;

//     while(phaseObserver < 1 || phaseObserver > 2)
//     {
//         std::cout << "Please try again, you can only choose between 1) On or 2) Off" << std::endl; 
//         std::cin >> phaseObserver;
//     }
//     std::cout << "---------------------------------------------------------------" << std::endl;
//     std::cout << "Please select if you want the Game Statistic Observers ON or OFF" << std::endl; 
//     std::cout << "1) Game Statistic Observers ON" << std::endl;
//     std::cout << "2) Game Statistic Observers OFF" << std::endl;

//     std::cin >> statObserver;

//     while(statObserver < 1 || statObserver > 2)
//     {
//         std::cout << "Please try again, you can only choose between 1) On or 2) Off" << std::endl; 
//         std::cin >> statObserver;
//     }
//     std::cout << "---------------------------------------------------------------" << std::endl;

//     // ***  Handle observers here  ***

//     // if(phaseObserver == 1)
//     // {
//     //     Map *model = new Map (MapLoader::createMap(mapNames[selectedMap-1])); 
//     //     MapObserver *view = new MapObserver(model);
//     //     MapContoller *contoller = new MapContoller(view, model);
//     //     contoller->controlMap();
//     //     delete view;
//     //     delete model;
//     //     delete contoller;
//     // }

//     //if(statObserver == 1) 
//     //{
//     //}
    
//     std::ifstream input(mapNames[selectedMap-1]);
//     std::vector<std::string> v = MapLoader::readFile(input);

//     if(MapLoader::validateFile(v))
//     {
//         //MapLoader::loadMap(mapNames[selectedMap-1]);
//         Deck gameDeck;
//     }
//     else
//     {
//         std::cout << std::endl;
//         std::cout << "The selected map is invalid, please start again." << std::endl;
//     }
    
//     std::cout << "---------------------------------------------------------------" << std::endl;

//     mapNames.clear();
// }
