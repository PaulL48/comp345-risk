#include "PlayerStrategies.h"

#include "Player.h"
#include "GameEngine.h"
#include <unordered_set>

PlayerStrategy::~PlayerStrategy()
{
}

std::ostream &operator<<(std::ostream &output, const PlayerStrategy &playerStrategy)
{
    return playerStrategy.print(output);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: HumanPlayerStrategy
//============================================================================================================================================================

HumanPlayerStrategy::HumanPlayerStrategy()
{
}

HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &)
{
}

HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &strategy)
{
    if (this == &strategy)
    {
        return *this;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &output, const HumanPlayerStrategy &)
{
    output << "Human strategy";
    return output;
}

std::ostream &HumanPlayerStrategy::print(std::ostream &output) const
{
    output << "Human Strategy";
    return output;
}

void HumanPlayerStrategy::issueOrder(Map &map, Player &player)
{
    // Issue deploy orders until all reinforcements are deployed
    while (player.getReinforcementsPendingDeployment() < player.getReinforcementPool())
    {
        std::cout << "================================================================================" << std::endl;
        std::cout << "Issue deployment orders to distribute all your reinforcements" << std::endl;
        std::cout << "Current orders are:" << std::endl;
        for (const auto *order : player.getOrders().getList())
        {
            std::cout << "\t- " << *order << std::endl;
        }
        std::cout << std::endl;

        InputUtilities::executeMenuAction(
            "Actions: ",
            std::vector<std::string>{"Issue deploy order", "Delete deploy order"},
            std::vector<std::function<void(void)>>{
                std::bind(&HumanPlayerStrategy::deploy, *this, std::ref(player), std::ref(map)),
                std::bind(&HumanPlayerStrategy::deleteOrder, *this, std::ref(player), std::ref(map))
            }
        );
    }

    bool stopOrders = false;
    while (!stopOrders)
    {
        std::cout << "================================================================================" << std::endl;
        std::cout << "Issue other orders to try and conquer the world" << std::endl;
        std::cout << "Current orders are:" << std::endl;
        for (const auto *order : player.getOrders().getList())
        {
            std::cout << "\t- " << *order << std::endl;
        }
        InputUtilities::executeMenuAction(
            "Actions: ",
            std::vector<std::string>{"Issue attack order", "Issue defense order", "Play a card", "Delete an order", "Stop Issuing Orders"},
            std::vector<std::function<void(void)>>{
                std::bind(&HumanPlayerStrategy::attack, *this, std::ref(player), std::ref(map)),
                std::bind(&HumanPlayerStrategy::defend, *this, std::ref(player), std::ref(map)),
                std::bind(&HumanPlayerStrategy::playCard, *this, std::ref(player), std::ref(map)),
                std::bind(&HumanPlayerStrategy::deleteNonDeployOrder, *this, std::ref(player), std::ref(map)),
                std::bind(&HumanPlayerStrategy::stop, *this, std::ref(player), std::ref(stopOrders))
            }
        );
    }
}

std::vector<Territory> HumanPlayerStrategy::toAttack(const Map &map, const Player &player)
{
    std::unordered_set<Territory> attackOptions; // Using an unordered set prevents duplication
    std::vector<Territory> ownedTerritories = map.getPlayersTerritories(player);
    for (Territory territory : ownedTerritories)
    {
        const std::unordered_set<Territory>* neighborTerritories = map.getNeighbors(territory);
        for (Territory neighborTerritory : *neighborTerritories)
        {
            if (neighborTerritory.getOwningPlayer() == nullptr || *neighborTerritory.getOwningPlayer() != player)
            {
                attackOptions.insert(neighborTerritory);
            }
        }
    }

    std::vector<Territory> result;
    result.insert(result.end(), attackOptions.begin(), attackOptions.end());
    return result;
}

std::vector<Territory> HumanPlayerStrategy::toDefend(const Map &map, const Player &player)
{
    return map.getPlayersTerritories(player);
}

PlayerStrategy *HumanPlayerStrategy::clone() const
{
    return new HumanPlayerStrategy(*this);
}

void HumanPlayerStrategy::deploy(Player &player, Map& map)
{
    // Choose territory and number of armies
    std::vector<Territory> toDefend = this->toDefend(map, player);
    Territory &territory = InputUtilities::getMenuChoice("Choose a territory to deploy to: ", toDefend);
    std::size_t amount = InputUtilities::getRangedInput("Choose the number of armies to deploy: ", 1, player.getReinforcementPool() - player.getReinforcementsPendingDeployment());
    player.getOrders().addToList(OrderBuilder::buildDeployOrder(&map, &player, territory, amount));
}

void HumanPlayerStrategy::deleteOrder(Player &player, Map&)
{
    std::vector<std::string> orders;
    std::stringstream ss;
    ss << "Choose an order to delete: " << std::endl;
    std::size_t i = 1;
    for (const Order* order : player.getOrders().getList())
    {
        // Add numbering
        ss << i++ << ") " << *order << std::endl;
    }

    std::size_t choice = InputUtilities::getRangedInput(ss.str(), 1, player.getOrders().getList().size());
    player.getOrders().remove(*player.getOrders().getList().at(choice - 1));
}

void HumanPlayerStrategy::attack(Player &player, Map& map)
{
    std::vector<Territory> toAttack = this->toAttack(map, player);
    Territory &target = InputUtilities::getMenuChoice("Choose a territory to attack: ", toAttack);
    std::vector<Territory> playerTerritoriesList = map.getPlayersTerritories(player);
    std::unordered_set<Territory> playerTerritories(playerTerritoriesList.begin(), playerTerritoriesList.end());
    const std::unordered_set<Territory>* targetNeighbors = map.getNeighbors(target);

    if (targetNeighbors == nullptr)
    {
        std::cout << "Something went wrong. Target territory: " << target << " does not exist in the map" << std::endl;
        return;
    }

    std::unordered_set<Territory> attackCandidates = SetUtilities::setIntersect(playerTerritories, *targetNeighbors);

    if (attackCandidates.size() == 0)
    {
        std::cout << "You have no territories that are neighbors to the selected target" << std::endl;
        return;
    }

    std::vector<Territory> attackCandidatesList(attackCandidates.begin(), attackCandidates.end());
    auto it = std::remove_if(attackCandidatesList.begin(), attackCandidatesList.end(), [&player](Territory& t) { return t.getOccupyingArmies() + player.getReinforcementsPendingDeployment(t) == 0; });
    if (it != attackCandidatesList.end())
    {
        attackCandidatesList.erase(it);
    }

    if (attackCandidatesList.empty())
    {
        std::cout << "You have no territories with armies adjacent to the target" << std::endl;
        return;
    }


    Territory &source = InputUtilities::getMenuChoice("Choose territory to attack from: ", attackCandidatesList);

    // We need to get the number of armies deployed to the territory as the number
    std::size_t amount = InputUtilities::getRangedInput("Choose the number of armies to attack with: ", 1, source.getOccupyingArmies() + player.getReinforcementsPendingDeployment(source));
    player.getOrders().addToList(OrderBuilder::buildAdvanceOrder(&map, &player, source, target, amount));
}

void HumanPlayerStrategy::defend(Player &player, Map& map)
{
    std::vector<Territory> toDefend = this->toDefend(map, player);
    Territory &target = InputUtilities::getMenuChoice("Choose a territory to defend: ", toDefend);
    std::vector<Territory> playerTerritoriesList = map.getPlayersTerritories(player);
    std::unordered_set<Territory> playerTerritories(playerTerritoriesList.begin(), playerTerritoriesList.end());
    const std::unordered_set<Territory>* targetNeighbors = map.getNeighbors(target);

    if (targetNeighbors == nullptr)
    {
        std::cout << "Something went wrong. Target territory: " << target << " does not exist in the map" << std::endl;
        return;
    }

    std::unordered_set<Territory> attackCandidates = SetUtilities::setIntersect(playerTerritories, *targetNeighbors);

    if (attackCandidates.size() == 0)
    {
        std::cout << "You have no territories that are neighbors to the selected target" << std::endl;
        return;
    }

    std::vector<Territory> attackCandidatesList(attackCandidates.begin(), attackCandidates.end());
    auto it = std::remove_if(attackCandidatesList.begin(), attackCandidatesList.end(), [&player](Territory& t) { return t.getOccupyingArmies() + player.getReinforcementsPendingDeployment(t) == 0; });
    if (it != attackCandidatesList.end())
    {
        attackCandidatesList.erase(it);
    }

    if (attackCandidatesList.empty())
    {
        std::cout << "You have no territories with armies adjacent to the target" << std::endl;
        return;
    }


    Territory &source = InputUtilities::getMenuChoice("Choose territory to defend from: ", attackCandidatesList);

    // We need to get the number of armies deployed to the territory as the number
    std::size_t amount = InputUtilities::getRangedInput("Choose the number of armies to defend with: ", 1, source.getOccupyingArmies() + player.getReinforcementsPendingDeployment(source));

    player.getOrders().addToList(OrderBuilder::buildAdvanceOrder(&map, &player, source, target, amount));
}

void HumanPlayerStrategy::playCard(Player &player, Map& map)
{

    std::vector<std::string> cards;
    std::stringstream ss;
    ss << "Choose a card to play: " << std::endl;
    std::size_t i = 1;
    for (const Card* card : player.getCards().getList())
    {
        ss << i++ << ") " << *card << std::endl;
    }

    std::size_t choice = InputUtilities::getRangedInput(ss.str(), 1, player.getCards().getList().size());
    Card *card = player.getCards().getList().at(choice - 1);
    switch (card->discriminant())
    {
    case 0:
        this->bomb(player, map);
        break;
    case 1:
        this->reinforce(player, map);
        break;
    case 2:
        this->blockade(player, map);
        break;
    case 3:
        this->airlift(player, map);
        break;
    case 4:
        this->diplomacy(player, map);
        break;
    }
    player.getCards().playCard(*card, player.getGameEngine().getDeck(), player.getOrders());
}

void HumanPlayerStrategy::deleteNonDeployOrder(Player &player, Map&)
{
    std::vector<std::string> orders;
    std::stringstream ss;
    ss << "Choose an order to delete: " << std::endl;
    for (const Order* order : player.getOrders().getList())
    {
        ss << "- " << *order << std::endl;
    }

    std::size_t choice = InputUtilities::getRangedInput(ss.str(), 1, player.getOrders().getList().size());
    if (player.getOrders().getList().at(choice)->getExecutionPriority() == DEPLOY_PRIORITY)
    {
        std::cout << "Cannot delete a deployment order once all your reinforcements are deployed" << std::endl;
        return;
    }

    player.getOrders().remove(*player.getOrders().getList().at(choice - 1));
}

void HumanPlayerStrategy::stop(Player &, bool &stop)
{
    std::size_t choice = InputUtilities::getNumericalMenuChoice("Are you sure you would like to stop adding orders?", std::vector<std::string>{"Yes", "No"});
    if (choice == 0)
    {
        stop = true;
    }
}

void HumanPlayerStrategy::bomb(Player &player, Map &map)
{
    std::vector<Territory> toAttack = this->toAttack(map, player);
    Territory &target = InputUtilities::getMenuChoice("Choose a territory to bomb: ", toAttack);
    player.getOrders().addToList(OrderBuilder::buildBombOrder(&map, &player, target));
}

void HumanPlayerStrategy::reinforce(Player &player, Map &map)
{
    player.getOrders().addToList(OrderBuilder::buildReinforcement(&map, &player));
}

void HumanPlayerStrategy::blockade(Player &player, Map &map)
{
    std::vector<Territory> toDefend = this->toDefend(map, player);
    Territory &target = InputUtilities::getMenuChoice("Choose a territory to blockade: ", toDefend);
    player.getOrders().addToList(OrderBuilder::buildBlockadeOrder(&map, &player, target));
}

void HumanPlayerStrategy::airlift(Player &player, Map &map)
{
    // Pick a destination territory
    // Pick a source
    // Pick the number of armies
    std::vector<Territory> toDefend = this->toDefend(map, player);
    Territory &target = InputUtilities::getMenuChoice("Choose a territory to airlift to: ", toDefend);


    std::vector<Territory> candidates = this->toDefend(map, player);
    auto it = std::remove_if(candidates.begin(), candidates.end(), [&player, &target](Territory& t) { return t.getOccupyingArmies() == 0 || t == target; });
    if (it != candidates.end())
    {
        candidates.erase(it);
    }

    if (candidates.empty())
    {
        std::cout << "You have no territories with armies to airlift from" << std::endl;
        return;
    }
    Territory &source = InputUtilities::getMenuChoice("Choose a territory to airlift from: ", candidates);
    std::size_t amount = InputUtilities::getRangedInput("Choose the number of armies to defend with: ", 1, player.getReinforcementsPendingDeployment(source) + source.getOccupyingArmies());
    player.getOrders().addToList(OrderBuilder::buildAirlift(&map, &player, source, target, amount));
}

void HumanPlayerStrategy::diplomacy(Player &player, Map &map)
{
    // Pick a player
    std::unordered_set<const Player*> playersSet;
    for (const auto& territory : map.getGraph())
    {
        if (territory.getOwningPlayer() != nullptr && *territory.getOwningPlayer() != player)
        {
            playersSet.insert(territory.getOwningPlayer());
        }
    }

    std::vector<const Player*> players(playersSet.begin(), playersSet.end());

    std::stringstream ss;
    std::size_t i = 1;
    ss << "Choose a player to enter peace with: " << std::endl;
    for (const Player* player : players)
    {
        ss << i << ") " << *player << std::endl;
    }

    std::size_t choice = InputUtilities::getRangedInput(ss.str(), 1, players.size());
    player.getOrders().addToList(OrderBuilder::buildNegotiate(&map, &player, const_cast<Player*>(players.at(choice - 1))));
}

//============================================================================================================================================================
// CLASS DEFINITIONS: AggressivePlayerStrategy
//============================================================================================================================================================

AggressivePlayerStrategy::AggressivePlayerStrategy()
{
}

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &)
{
}

AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &strategy)
{
    if (this == &strategy)
    {
        return *this;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &output, const AggressivePlayerStrategy &)
{
    output << "Aggressive strategy";
    return output;
}

std::ostream &AggressivePlayerStrategy::print(std::ostream &output) const
{
    output << "Aggressive Strategy";
    return output;
}

void AggressivePlayerStrategy::issueOrder(Map &, Player &)
{
}

std::vector<Territory> AggressivePlayerStrategy::toAttack(const Map &, const Player &)
{
    return std::vector<Territory>();
}

std::vector<Territory> AggressivePlayerStrategy::toDefend(const Map &, const Player &)
{
    return std::vector<Territory>();
}

PlayerStrategy *AggressivePlayerStrategy::clone() const
{
    return new AggressivePlayerStrategy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: BenevolentPlayerStrategy
//============================================================================================================================================================

BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &)
{
}

BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &strategy)
{
    if (this == &strategy)
    {
        return *this;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &output, const BenevolentPlayerStrategy &)
{
    output << "Benevolent strategy";
    return output;
}

std::ostream &BenevolentPlayerStrategy::print(std::ostream &output) const
{
    output << "Benevolent Strategy";
    return output;
}

void BenevolentPlayerStrategy::issueOrder(Map &, Player &)
{
}

std::vector<Territory> BenevolentPlayerStrategy::toAttack(const Map &, const Player &)
{
    return std::vector<Territory>();
}

std::vector<Territory> BenevolentPlayerStrategy::toDefend(const Map &, const Player &)
{
    return std::vector<Territory>();
}

PlayerStrategy *BenevolentPlayerStrategy::clone() const
{
    return new BenevolentPlayerStrategy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: NeutralPlayerStrategy
//============================================================================================================================================================

NeutralPlayerStrategy::NeutralPlayerStrategy()
{
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &)
{
}

NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &strategy)
{
    if (this == &strategy)
    {
        return *this;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &output, const NeutralPlayerStrategy &)
{
    output << "Neutral strategy";
    return output;
}

std::ostream &NeutralPlayerStrategy::print(std::ostream &output) const
{
    output << "Neutral Strategy";
    return output;
}

void NeutralPlayerStrategy::issueOrder(Map &, Player &)
{
}

std::vector<Territory> NeutralPlayerStrategy::toAttack(const Map &, const Player &)
{
    return std::vector<Territory>();
}

std::vector<Territory> NeutralPlayerStrategy::toDefend(const Map &, const Player &)
{
    return std::vector<Territory>();
}

PlayerStrategy *NeutralPlayerStrategy::clone() const
{
    return new NeutralPlayerStrategy(*this);
}
