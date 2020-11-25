#include "PlayerStrategies.h"

PlayerStrategy::~PlayerStrategy()
{
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

void HumanPlayerStrategy::issueOrder(const Map &, Player &)
{
}

std::vector<Territory> HumanPlayerStrategy::toAttack(const Map &, const Player &)
{
    return std::vector<Territory>();
}

std::vector<Territory> HumanPlayerStrategy::toDefend(const Map &, const Player &)
{
    return std::vector<Territory>();
}

PlayerStrategy *HumanPlayerStrategy::clone() const
{
    return new HumanPlayerStrategy(*this);
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

void AggressivePlayerStrategy::issueOrder(const Map &, Player &)
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

void BenevolentPlayerStrategy::issueOrder(const Map &, Player &)
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

void NeutralPlayerStrategy::issueOrder(const Map &, Player &)
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
