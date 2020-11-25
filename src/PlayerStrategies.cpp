#include "PlayerStrategies.h"


//============================================================================================================================================================
// CLASS DEFINITIONS: HumanPlayerStrategy
//============================================================================================================================================================

void HumanPlayerStrategy::issueOrder(const Map& map, Player& player)
{

}

std::vector<Territory>& HumanPlayerStrategy::toAttack(const Map& map, const Player& player)
{

}

std::vector<Territory>& HumanPlayerStrategy::toDefend(const Map& map, const Player& player)
{

}

PlayerStrategy* HumanPlayerStrategy::clone() const
{
    return new HumanPlayerStrategy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: AggressivePlayerStrategy
//============================================================================================================================================================

void AggressivePlayerStrategy::issueOrder(const Map& map, Player& player)
{

}

std::vector<Territory>& AggressivePlayerStrategy::toAttack(const Map& map, const Player& player)
{

}

std::vector<Territory>& AggressivePlayerStrategy::toDefend(const Map& map, const Player& player)
{

}

PlayerStrategy* AggressivePlayerStrategy::clone() const
{
    return new AggressivePlayerStrategy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: BenevolentPlayerStrategy
//============================================================================================================================================================

void BenevolentPlayerStrategy::issueOrder(const Map& map, Player& player)
{

}

std::vector<Territory>& BenevolentPlayerStrategy::toAttack(const Map& map, const Player& player)
{

}

std::vector<Territory>& BenevolentPlayerStrategy::toDefend(const Map& map, const Player& player)
{
    
}

PlayerStrategy* BenevolentPlayerStrategy::clone() const
{
    return new BenevolentPlayerStrategy(*this);
}

//============================================================================================================================================================
// CLASS DEFINITIONS: NeutralPlayerStrategy
//============================================================================================================================================================

void NeutralPlayerStrategy::issueOrder(const Map& map, Player& player)
{

}

std::vector<Territory>& NeutralPlayerStrategy::toAttack(const Map& map, const Player& player)
{

}

std::vector<Territory>& NeutralPlayerStrategy::toDefend(const Map& map, const Player& player)
{

}

PlayerStrategy* NeutralPlayerStrategy::clone() const
{
    return new NeutralPlayerStrategy(*this);
}
