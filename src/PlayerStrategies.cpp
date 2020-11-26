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
