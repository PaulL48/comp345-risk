#include "GameEngine.h"

int main()
{
    std::size_t startAgain = 0;

    while (startAgain == 0)
    {
        GameEngine gameEngine;
        gameEngine.configure();
        gameEngine.startupPhase();
        gameEngine.mainGameLoop();

        startAgain = InputUtilities::getNumericalMenuChoice("Would you like to play again?", std::vector<std::string>{"Yes", "No"});
    }

    return 0;
}