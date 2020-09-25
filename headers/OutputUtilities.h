#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T>& set);

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T*>& set);

template <typename T, typename U>
std::ostream& operator<<(std::ostream& output, const std::unordered_map<T, U>& map);

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::stack<T*>& stack);

//============================================================================================================================================================
// TEMPLATE FUNCTION DEFINITIONS
//============================================================================================================================================================

template <typename T, typename U>
std::ostream& operator<<(std::ostream& output, const std::unordered_map<T, U>& map)
{
    auto it = map.cbegin();
    output << "{ ";
    if (!map.empty())
    {
        output << (*it).first << ": " << (*it).second;
        ++it;
    }

    for (; it != map.cend(); ++it)
    {
        output << ", " << (*it).first << ": " << (*it).second;
    }
    output << " }";
    return output;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T*>& set)
{
    auto it = set.cbegin();
    output << "{ ";
    if (!set.empty())
    {
        output << **it;
        ++it;
    }

    for (; it != set.cend(); ++it)
    {
        output << ", " << **it;
    }
    output << " }";
    return output;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T>& set)
{
    auto it = set.cbegin();
    output << "{ ";
    if (!set.empty())
    {
        output << *it;
        ++it;
    }

    for (; it != set.cend(); ++it)
    {
        output << ", " << *it;
    }
    output << " }";
    return output;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& output, const std::stack<T*, U>& stack)
{
    // Unfortunately the stack container does not support iteration, so
    // to access all elements we need to copy it and pop it
    std::stack<T*, U> tempStack = stack;
    output << "[ ";
    if (!tempStack.empty())
    {
        output << *tempStack.top();
        tempStack.pop();
    }

    while (!tempStack.empty())
    {
        output << ", " << tempStack.top();
    }

    output << " ]";
    return output;
}
