#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <functional>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

namespace MenuUtilities
{
    template <typename T>
    const T& getValidatedMenuChoice(const std::string& headerMessage, const std::vector<T>& list);

    template <typename T>
    T& getMutableValidatedMenuChoice(const std::string& headerMessage, std::vector<T>& list);

    template <typename T>
    std::size_t getValidatedNumericalChoice(const std::string& headerMessage, const std::vector<T>& list);

    int getRangeValidatedInput(int lowerBound, int upperBound);

    template <typename T>
    void executeMenuAction(const std::string& headerMessage, const std::vector<T>& choiceList, const std::vector<std::function<void(void)>>& actions);

    template <typename T>
    void executeMenuActionWithExit(const std::string& headerMessage, const std::vector<T>& list,  const std::vector<std::function<void(void)>>& actions, const std::string& exitString, bool& exit);


}

class Player{
    private:
        std::string* playerName;
        std::vector<Territory>* territoriesAttack;
        std::vector<Territory>* territoriesDefend;
        Hand* cards;
        OrdersList* orders;
        int* reinforcementPool;
        bool* conqueredTerritory;
    public:
        // Create a named player with an empty hand
        Player(const std::string& name); 
        Player(const std::string& playerName,const std::vector<Territory>& territoriesAttack, const std::vector<Territory>& territoriesDefend, const Hand& cards, const OrdersList& orders);
        Player(const Player& player);
        Player();
        Player& operator= (const Player& player);
        bool operator==(const Player& player) const;
        bool operator!=(const Player& player) const;
        ~Player();
        friend std::ostream& operator<<( std::ostream &output, const Player& player);
        std::vector<Territory>& toAttack();
        std::vector<Territory>& toDefend();
        Hand& getCards();
        OrdersList& getOrders();
        std::string& getPlayerName();
        void issueOrder(const Map& map);
        void addArmies(int add);
        int getReinforcementPool() const;
        void setConqueredTerritory(bool conqueredTerritory);
        bool getConqueredTerritory() const;

        void specifyDeploymentOrder(const Map& map);
        void specifyOrderDeletion();
        void specifyAttackOrder(const Map& map);
        void specifyDefendOrder();
        void chooseCardToPlay();

        // Player fills their order list and plays any cards

        // Return the number of armies queued to reinforce various territories
        int getReinforcementsPendingDeployment();

};

template <typename T>
const T& MenuUtilities::getValidatedMenuChoice(const std::string& headerMessage, const std::vector<T>& list)
{
    if (list.size() == 0)
    {
        std::exit(1); // Nothing meaningful or valid can be returned here.
    }

    bool inputInvalid = true;
    std::size_t convertedInput;
    while (inputInvalid)
    {
        if (headerMessage.size() != 0)
        {
            std::cout << headerMessage << std::endl;
        }
        
        
        for (std::size_t i = 0; i < list.size(); ++i)
        {
            std::cout << i + 1 << ") " << list.at(i) << std::endl;
        }
        std::cout << "Please enter a value between 1 and " << list.size() << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            inputInvalid= true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        try
        {
            inputInvalid = false;
            convertedInput = std::stoull(input);
        }
        catch(const std::exception& e)
        {
            inputInvalid = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (convertedInput < 1 || convertedInput > list.size())
        {
            inputInvalid = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    return list.at(convertedInput - 1);
}

template <typename T>
T& MenuUtilities::getMutableValidatedMenuChoice(const std::string& headerMessage, std::vector<T>& list)
{
    if (list.size() == 0)
    {
        std::exit(1); // Nothing meaningful or valid can be returned here.
    }

    bool inputInvalid = true;
    std::size_t convertedInput;
    while (inputInvalid)
    {
        if (headerMessage.size() != 0)
        {
            std::cout << headerMessage << std::endl;
        }
        
        
        for (std::size_t i = 0; i < list.size(); ++i)
        {
            std::cout << i + 1 << ") " << list.at(i) << std::endl;
        }
        std::cout << "Please enter a value between 1 and " << list.size() << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            inputInvalid= true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        try
        {
            inputInvalid = false;
            convertedInput = std::stoull(input);
        }
        catch(const std::exception& e)
        {
            inputInvalid = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (convertedInput < 1 || convertedInput > list.size())
        {
            inputInvalid = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    return list.at(convertedInput - 1);
}

template <typename T>
std::size_t MenuUtilities::getValidatedNumericalChoice(const std::string& headerMessage, const std::vector<T>& list)
{
    if (list.size() == 0)
    {
        std::exit(1); // Nothing meaningful or valid can be returned here.
    }

    bool inputInvalid = true;
    std::size_t convertedInput;
    while (inputInvalid)
    {
        if (headerMessage.size() != 0)
        {
            std::cout << headerMessage << std::endl;
        }
        
        
        for (std::size_t i = 0; i < list.size(); ++i)
        {
            std::cout << i + 1 << ") " << list.at(i) << std::endl;
        }
        std::cout << "Please enter a value between 1 and " << list.size() << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            inputInvalid= true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        try
        {
            inputInvalid = false;
            convertedInput = std::stoull(input);
        }
        catch(const std::exception& e)
        {
            inputInvalid = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (convertedInput < 1 || convertedInput > list.size())
        {
            inputInvalid = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    return convertedInput - 1;
}

template <typename T>
void MenuUtilities::executeMenuAction(const std::string& headerMessage, const std::vector<T>& choiceList, const std::vector<std::function<void(void)>>& actions)
{
    if (choiceList.size() == 0 || choiceList.size() != actions.size())
    {
        std::exit(1); // Nothing meaningful or valid can be returned here.
    }

    bool inputInvalid = true;
    std::size_t convertedInput;
    while (inputInvalid)
    {
        if (headerMessage.size() != 0)
        {
            std::cout << headerMessage << std::endl;
        }
        
        
        for (std::size_t i = 0; i < choiceList.size(); ++i)
        {
            std::cout << i + 1 << ") " << choiceList.at(i) << std::endl;
        }
        std::cout << "Please enter a value between 1 and " << choiceList.size() << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            inputInvalid= true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        try
        {
            inputInvalid = false;
            convertedInput = std::stoull(input);
        }
        catch(const std::exception& e)
        {
            inputInvalid = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (convertedInput < 1 || convertedInput > choiceList.size())
        {
            inputInvalid = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    actions.at(convertedInput - 1)(); // execute the actions
}

template <typename T>
void MenuUtilities::executeMenuActionWithExit(const std::string& headerMessage, const std::vector<T>& list, const std::vector<std::function<void(void)>>& actions, const std::string& exitString, bool& exit)
{
    if (list.size() == 0)
    {
        std::exit(1); // Nothing meaningful or valid can be returned here.
    }

    bool inputInvalid = true;
    std::size_t convertedInput;
    while (inputInvalid)
    {
        if (headerMessage.size() != 0)
        {
            std::cout << headerMessage << std::endl;
        }
        
        
        for (std::size_t i = 0; i < list.size(); ++i)
        {
            std::cout << i + 1 << ") " << list.at(i) << std::endl;
        }
        std::cout << "Please enter a value between 1 and " << list.size() << ": ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            inputInvalid= true;
            std::cout << "No input received" << std::endl << std::endl;
            continue;
        }

        if (input == exitString)
        {
            exit = true;
            return; // This produces a very large unsigned integer
        }

        try
        {
            inputInvalid = false;
            convertedInput = std::stoull(input);
        }
        catch(const std::exception& e)
        {
            inputInvalid = true;
            std::cout << "Invalid input" << std::endl << std::endl;
            continue;
        }

        if (convertedInput < 1 || convertedInput > list.size())
        {
            inputInvalid = true;
            std::cout << "Input out of range" << std::endl << std::endl;
            continue;
        }
    }

    actions.at(convertedInput - 1)();
}



#endif
