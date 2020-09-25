#include <unordered_set>
#include <unordered_map>

// Return the keys of an unordered map as an unordered set
template <typename T, typename U>
std::unordered_set<T> getKeys(const std::unordered_map<T, U>& map);

// Return whether the second set is a subset of the first
template <typename T>
bool isSubset(const std::unordered_set<T>& set, const std::unordered_set<T>& subset);

// Return the set difference of the two sets
template <typename T>
std::unordered_set<T> setDifference(const std::unordered_set<T>& minuend, const std::unordered_set<T>& subtrahend);

//============================================================================================================================================================
// TEMPLATE FUNCTION DEFINITIONS
//============================================================================================================================================================

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
