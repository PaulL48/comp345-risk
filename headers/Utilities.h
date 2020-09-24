#include <unordered_set>
#include <unordered_map>
#include <iostream>

template <typename T, typename U>
std::unordered_set<T> getKeys(const std::unordered_map<T, U>& map);

template <typename T>
bool isSubset(const std::unordered_set<T>& set, const std::unordered_set<T>& subset);

template <typename T>
std::unordered_set<T> setDifference(const std::unordered_set<T>& minuend, const std::unordered_set<T>& subtrahend);

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T>& set);

template <typename T, typename U>
std::ostream& operator<<(std::ostream& output, const std::unordered_map<T, U>& map);

// O(map.size)
template <typename T, typename U>
std::unordered_set<T> getKeys(const std::unordered_map<T, U>& map)
{
    std::unordered_set<T> keys;
    for (const auto & [key, value]: map)
    {
        keys.insert(key);
    }
    return keys;
}

// O(subset.size)
template <typename T>
bool isSubset(const std::unordered_set<T>& set, const std::unordered_set<T>& subset)
{
    for (const T& element : subset)
    {
        if (set.count(element) == 0)
        {
            return false;
        }
    }

    return true;
}

// O(minuend.size)
template <typename T>
std::unordered_set<T> setDifference(const std::unordered_set<T>& minuend, const std::unordered_set<T>& subtrahend)
{
    std::unordered_set<T> result;
    for (const T& element : minuend)
    {
        if (subtrahend.count(element) == 0)
        {
            result.insert(element);
        }
    }
    return result;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& output, const std::unordered_map<T, U>& map)
{
    auto it = map.cbegin();
    output << "{" << std::endl;
    if (!map.empty())
    {
        output << "\t" << (*it).first << ": " << (*it).second;
        ++it;
    }

    for (; it != map.cend(); ++it)
    {
        output << "," << std::endl; 
        output << "\t" << (*it).first << ": " << (*it).second;
    }
    output << std::endl;
    output << "}";
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
