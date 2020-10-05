#ifndef MAP_H
#define MAP_H

#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>


//============================================================================================================================================================
// TEMPLATE FUNCTION DECLARATIONS: OutputUtilities
//============================================================================================================================================================

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::unordered_set<T> &set);

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::unordered_set<T *> &set);

template <typename T, typename U>
std::ostream &operator<<(std::ostream &output, const std::unordered_map<T, U> &map);

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::stack<T *> &stack);

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::vector<T> &vector);

//============================================================================================================================================================
// TEMPLATE FUNCTION DECLARATIONS: SetUtilities
//============================================================================================================================================================

namespace SetUtilities
{
    // Return the keys of an unordered map as an unordered set
    template <typename T, typename U>
    std::unordered_set<T> getKeys(const std::unordered_map<T, U> &map);

    // Return whether the second set is a subset of the first
    template <typename T>
    bool isSubset(const std::unordered_set<T> &set,
                  const std::unordered_set<T> &subset);

    // Return the set difference of the two sets
    template <typename T>
    std::unordered_set<T> setDifference(const std::unordered_set<T> &minuend,
                                        const std::unordered_set<T> &subtrahend);
} // namespace SetUtilities

//============================================================================================================================================================
// TEMPLATE CLASS DECLARATION: DepthFirstIterator
//============================================================================================================================================================

template <typename T>
using AdjacencyList = std::unordered_map<T, std::unordered_set<T>>;

template <typename T>
using NeighborList = typename AdjacencyList<T>::mapped_type;

template <typename T>
class DepthFirstIterator
{
public:
    explicit DepthFirstIterator(const AdjacencyList<T> *adjacencyList); // Constructor

    DepthFirstIterator(const DepthFirstIterator &dfi); // Copy constructor

    ~DepthFirstIterator(); // Destructor

    DepthFirstIterator &operator=(const DepthFirstIterator &dfi); // Copy assignment

    template <typename U>
    friend std::ostream &operator<<(std::ostream &output,
                                    const DepthFirstIterator<U> &dfi); // Stream output

    // Return whether two DFS iterators are at the same point in iteration on
    // the same adjacency list
    bool operator==(const DepthFirstIterator &dfi) const;

    // Return the negation of operator==
    bool operator!=(const DepthFirstIterator &dfi) const;

    // Advance the iterator to the next vertex
    DepthFirstIterator &operator++();

    DepthFirstIterator operator+(std::size_t i);

    // Get the vertex the iterator is currently referencing
    const T &operator*() const;

    // Get the vertex the iterator is currently referencing
    const T *operator->() const;

private:
    // Tracks vertexes already visited.
    // Improves performance and prevents cyclic graphs looping infinitely
    std::unordered_set<const NeighborList<T> *> *visited;

    // Track upcoming nodes during iteration
    std::stack<const T *, std::vector<const T *>> *stack;

    // Non-owning pointer to adjacency list. Used to get the neighbors of a
    // neighbor
    const AdjacencyList<T> *adjacencyList;
};

//============================================================================================================================================================
// TEMPLATE CLASS DECLARATION: Graph
//============================================================================================================================================================

template <typename T>
class Graph
{
public:
    Graph(); // Default constructor

    Graph(const Graph<T> &graph); // Copy constructor

    ~Graph(); // Destructor

    Graph &operator=(const Graph<T> &graph); // Copy assignment

    template <typename U>
    friend std::ostream &operator<<(std::ostream &output,
                                    const Graph<U> &graph); // Stream output

    // Return whether two graphs are identical
    bool operator==(const Graph<T> &graph) const;

    // Return whether this graph is a connected graph
    bool isConnected() const;

    // Return whether this graph is a subgraph of the supplied graph
    bool isSubgraphOf(const Graph<T> &graph) const;

    // Insert the vertex into the graph if it is not already present
    void insert(const T &vertex);

    // Connect two vertices if both vertices exist
    void connect(const T &vertex1, const T &vertex2);

    // Remove the vertex and all edges to it from the graph
    void erase(const T &vertex);

    void merge(const T& vertex1, const T& vertex2);

    std::size_t size() const;

    // Return iterator to the start of the container
    DepthFirstIterator<T> begin() const;

    // Return iterator past the end of the container
    DepthFirstIterator<T> end() const;

    // Return the first element of the graph that satisfies the supplied
    // predicate, or nullptr if none are found
    template <typename F>
    const T *findIf(F predicate) const;

private:
    // Owning pointer to adjacency list
    AdjacencyList<T> *adjacencyList;
};

//============================================================================================================================================================
// CLASS DECLARATION: Territory
//============================================================================================================================================================

class Player
{
    // STUB
public:
    friend std::ostream &operator<<(std::ostream &output, const Player &player);

private:
    std::string name;
};

class Territory
{
public:
    Territory();                                              // Default constructor
    Territory(int id, const std::string &name, int x, int y); // Constructor
    Territory(const Territory &territory);                    // Copy constructor
    ~Territory();                                             // Destructor
    Territory &operator=(const Territory &territory);         // Copy assignment
    friend std::ostream &operator<<(std::ostream &output,
                                    const Territory &territory); // Stream insertion

    // Return whether two territories have the same name and id
    bool operator==(const Territory &territory) const;
    bool operator!=(const Territory &territory) const;

    int getId() const;

    // Adding std::hash is necessary to allow Territory to be a key of an
    // associative container
    friend class std::hash<Territory>;

private:
    int *id;
    std::string *name;
    int *x;
    int *y;
    int *occupyingArmies;
    Player *ownedBy;
};

// Taken from Boost::hash_combine.
template <class T>
inline void hash_combine(std::size_t &seed, const T &v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std // Only ever extend std for std::hash
{
    template <>
    struct hash<Territory>
    {
        std::size_t operator()(const Territory &territory) const noexcept
        {
            // The hash function and operator== must be in agreement
            // So only values participating in operator== are hashed
            std::size_t seed = 0;
            hash_combine<int>(seed, *territory.id);
            hash_combine<std::string>(seed, *territory.name);
            return seed;
        }
    };
} // namespace std

//============================================================================================================================================================
// CLASS DECLARATION: Continent
//============================================================================================================================================================

class Continent
{
public:
    Continent(const std::string &name, int armyValue,
              const std::string &color);              // Constructor
    Continent(const Continent &continent);            // Copy constructor
    ~Continent();                                     // Destructor
    Continent &operator=(const Continent &continent); // Copy assignment
    friend std::ostream &operator<<(std::ostream &output,
                                    const Continent &continent); // Stream insertion

    // Add a territory to this continent
    void addTerritory(const Territory &territory);

    // Return whether the continent is a connected subgraph of territories
    bool isValidContinent(const Graph<Territory> &territories) const;

    // Get the territories of this continent
    std::unordered_set<Territory> getTerritories() const;

    // Connect two territories
    void connectTerritories(const Territory &territory1, const Territory &territory2);

    // Return a depth first iterator to a territory of this continent
    DepthFirstIterator<Territory> begin() const;

    // Return a past-the-end iterator to this continent
    DepthFirstIterator<Territory> end() const;

private:
    std::string *name;
    int* armyValue;
    std::string* color;
    Graph<Territory> *territories;
};

//============================================================================================================================================================
// CLASS DECLARATION: Map
//============================================================================================================================================================

enum class MapState
{
    VALID,
    NOT_CONNECTED_GRAPH,
    CONTINENTS_NOT_CONNECTED_SUBGRAPHS,
    TERRITORY_DOES_NOT_BELONG_TO_ONE_CONTINET
};

class Map
{
public:
    Map();                          // Constructor
    Map(const Map &map);            // Copy constructor
    ~Map();                         // Destructor
    Map &operator=(const Map &map); // Copy assignment
    friend std::ostream &operator<<(std::ostream &output,
                                    const Map &map); // Stream insertion

    // Validate the map and return the state of validation
    MapState validate() const;

    std::string getErrorString(MapState mapState) const;

    void addContinent(const Continent &continent);

    void addTerritory(const Territory &territory, int continentId);

    // Connect territories on this map
    void connectTerritories(int territoryId1, int territoryId2);

private:
    Graph<Territory> *territories;
    std::vector<Continent> *continents;
};

//============================================================================================================================================================
// TEMPLATE FUNCTION DEFINITIONS: OutputUtilities
//============================================================================================================================================================

template <typename T, typename U>
std::ostream &operator<<(std::ostream &output, const std::unordered_map<T, U> &map)
{
    auto it = map.cbegin();
    output << "{";
    if (!map.empty())
    {
        output << (*it).first << ": " << (*it).second;
        ++it;
    }

    for (; it != map.cend(); ++it)
    {
        output << ", " << (*it).first << ": " << (*it).second;
    }
    output << "}";
    return output;
}

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::unordered_set<T *> &set)
{
    auto it = set.cbegin();
    output << "{";
    if (!set.empty())
    {
        output << **it;
        ++it;
    }

    for (; it != set.cend(); ++it)
    {
        output << ", " << **it;
    }
    output << "}";
    return output;
}

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::unordered_set<T> &set)
{
    auto it = set.cbegin();
    output << "{";
    if (!set.empty())
    {
        output << *it;
        ++it;
    }

    for (; it != set.cend(); ++it)
    {
        output << ", " << *it;
    }
    output << "}";
    return output;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &output, const std::stack<T *, U> &stack)
{
    // Unfortunately the stack container adapter does not support iteration, so
    // to access all elements we need to copy it and pop it
    std::stack<T *, U> tempStack = stack;
    output << "[";
    if (!tempStack.empty())
    {
        output << *tempStack.top();
        tempStack.pop();
    }

    while (!tempStack.empty())
    {
        output << ", " << tempStack.top();
    }

    output << "]";
    return output;
}

template <typename T>
std::ostream &operator<<(std::ostream &output, const std::vector<T> &vector)
{
    auto it = vector.cbegin();
    output << "[";
    if (!vector.empty())
    {
        output << *it;
        ++it;
    }

    for (; it != vector.cend(); ++it)
    {
        output << *it;
    }

    output << "]";
    return output;
}

//============================================================================================================================================================
// TEMPLATE FUNCTION DEFINITIONS: SetUtilities
//============================================================================================================================================================

template <typename T, typename U>
std::unordered_set<T> SetUtilities::getKeys(const std::unordered_map<T, U> &map)
{
    std::unordered_set<T> keys;
    for (const auto &[key, value] : map)
    {
        keys.insert(key);
    }
    return keys;
}

template <typename T>
bool SetUtilities::isSubset(const std::unordered_set<T> &set,
                            const std::unordered_set<T> &subset)
{
    for (const T &element : subset)
    {
        if (set.count(element) == 0)
        {
            return false;
        }
    }

    return true;
}

template <typename T>
std::unordered_set<T>
SetUtilities::setDifference(const std::unordered_set<T> &minuend,
                            const std::unordered_set<T> &subtrahend)
{
    std::unordered_set<T> result;
    for (const T &element : minuend)
    {
        if (subtrahend.count(element) == 0)
        {
            result.insert(element);
        }
    }
    return result;
}

//============================================================================================================================================================
// TEMPLATE CLASS DEFINITIONS: DepthFirstIterator
//============================================================================================================================================================


template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const AdjacencyList<T> *adjacencyList) :
    visited(new std::unordered_set<const NeighborList<T> *>()),
    stack(new std::stack<const T *, std::vector<const T *>>()),
    adjacencyList(adjacencyList)
{
    if (adjacencyList != nullptr)
    {
        if (adjacencyList->empty())
        {
            // If the adjacency list is empty, set the iterator to end()
            this->adjacencyList = nullptr;
        }
        else
        {
            // The first vertex of the graph is pushed to the stack to start the
            // depth first traversal
            this->stack->push(&(this->adjacencyList->begin()->first));
        }
    }
}

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const DepthFirstIterator &dfi) :
    visited(new std::unordered_set<const NeighborList<T> *>(*dfi.visited)),
    stack(new std::stack<const T *, std::vector<const T *>>(*dfi.stack)),
    adjacencyList(dfi.adjacencyList)
{
}

template <typename T>
DepthFirstIterator<T>::~DepthFirstIterator()
{
    // Non-owning pointer this->adjacencyList is not deleted
    delete this->visited;
    delete this->stack;
}

template <typename T>
DepthFirstIterator<T> &
DepthFirstIterator<T>::operator=(const DepthFirstIterator<T> &dfi)
{
    if (&dfi == this)
    {
        return *this;
    }

    // Non-owning pointer can be trivially copied from incoming iterator
    this->adjacencyList = dfi.adjacencyList;

    // Remaining members invoke copy constructors
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
bool DepthFirstIterator<T>::operator==(const DepthFirstIterator<T> &dfi) const
{
    // Equivalence is: two iterators being at the same point of iteration over
    // the same adjacency list
    return this->adjacencyList == dfi.adjacencyList && *this->stack == *dfi.stack;
}

template <typename T>
bool DepthFirstIterator<T>::operator!=(const DepthFirstIterator<T> &dfi) const
{
    return !(*this == dfi);
}

template <typename T>
DepthFirstIterator<T> &DepthFirstIterator<T>::operator++()
{
    // Pop the current vertex from the stack so its neighbors can be added
    const T *current = this->stack->top();
    this->stack->pop();

    // Mark the current vertex as visited
    this->visited->insert(&(this->adjacencyList->at(*current)));

    // Push the current vertex's neighbors onto the stack if they haven't been
    // visited
    for (const T &neighbor : this->adjacencyList->at(*current))
    {
        if (this->visited->count(&(this->adjacencyList->at(neighbor))) == 0)
        {
            this->stack->push(&neighbor);
        }
    }

    // If iteration is complete, set the sentinel value of the pointer to become
    // equivalent to Graph<T>::end()
    if (this->stack->empty())
    {
        this->adjacencyList = nullptr;
        return *this;
    }

    return *this;
}

template <typename T>
DepthFirstIterator<T> DepthFirstIterator<T>::operator+(std::size_t count)
{
    DepthFirstIterator<T> result = *this;
    for (std::size_t i = 0; i < count && result.adjacencyList != nullptr; ++i)
    {
        ++result;
    }
    return result;
}

template <typename T>
const T &DepthFirstIterator<T>::operator*() const
{
    return *(this->stack->top());
}

template <typename T>
const T *DepthFirstIterator<T>::operator->() const
{
    return this->stack->top();
}

template <typename T>
std::ostream &operator<<(std::ostream &output, const DepthFirstIterator<T> &dfi)
{
    output << "{" << std::endl;
    output << "\tvisited: " << *dfi.visited << std::endl;
    output << "\tstack: " << *dfi.stack << std::endl;
    output << "\tgraph: " << *dfi.adjacencyList << std::endl;
    output << "}" << std::endl;
    return output;
}

//============================================================================================================================================================
// TEMPLATE CLASS DEFINITIONS: Graph
//============================================================================================================================================================

template <typename T>
Graph<T>::Graph() : adjacencyList(new AdjacencyList<T>())
{
}

template <typename T>
Graph<T>::~Graph()
{
    delete this->adjacencyList;
}

template <typename T>
Graph<T>::Graph(const Graph<T> &graph) :
    adjacencyList(new AdjacencyList<T>(*graph.adjacencyList))
{
}

template <typename T>
Graph<T> &Graph<T>::operator=(const Graph<T> &graph)
{
    if (&graph == this)
    {
        return *this;
    }

    // Invoke copy constructors
    *this->adjacencyList = *graph.adjacencyList;
    return *this;
}

template <typename T>
bool Graph<T>::operator==(const Graph<T> &graph) const
{
    // Equality is defferred to adjacency list equality
    return *this->adjacencyList == *graph.adjacencyList;
}

template <typename T>
std::ostream &operator<<(std::ostream &output, const Graph<T> &graph)
{
    output << *graph.adjacencyList;
    return output;
}

template <typename T>
bool Graph<T>::isConnected() const
{
    // Get all the vertices directly from the adjacency list
    std::unordered_set<T> vertices = SetUtilities::getKeys(*this->adjacencyList);

    // Traverse the graph using DFS
    std::unordered_set<T> reachableVertices;
    for (const T &vertex : *this)
    {
        reachableVertices.insert(vertex);
    }

    // If all the vertices are reachable, it is a connected graph
    return reachableVertices == vertices;
}

template <typename T>
bool Graph<T>::isSubgraphOf(const Graph<T> &graph) const
{
    // Algorithm Description:
    // A list of vertices is obtained via the set difference graph.vertices - thisGraph.vertices 
    // The supplied graph is transformed by removing those vertices and connections to those vertices 
    // If the transformed graph is equivalent to this graph, this graph is a subgraph

    std::unordered_set<T> subgraphVertices = SetUtilities::getKeys(*this->adjacencyList);
    std::unordered_set<T> graphVertices = SetUtilities::getKeys(*graph.adjacencyList);

    // Early test: If the vertices of this graph are not a subset of the
    // supplied graph, This graph cannot be a subgraph
    if (!SetUtilities::isSubset(graphVertices, subgraphVertices))
    {
        return false;
    }

    Graph<T> transformedGraph = graph;
    for (const T &vertex : SetUtilities::setDifference(graphVertices, subgraphVertices))
    {
        transformedGraph.erase(vertex);
    }

    return *this == transformedGraph;
}

template <typename T>
void Graph<T>::insert(const T &vertex)
{
    if (this->adjacencyList->count(vertex) == 0)
    {
        this->adjacencyList->insert(std::make_pair(vertex, NeighborList<T>()));
    }
}

template <typename T>
void Graph<T>::erase(const T &vertex)
{
    // Remove the vertex if it exists
    if (this->adjacencyList->count(vertex) != 0)
    {
        this->adjacencyList->erase(vertex);
    }

    // Remove all edges to the vertex
    for (auto &[vertexKey, neighbors] : *this->adjacencyList)
    {
        if (neighbors.count(vertex) != 0)
        {
            neighbors.erase(vertex);
        }
    }
}

template <typename T>
void Graph<T>::connect(const T &vertex1, const T &vertex2)
{
    // Assure vertices exist and that they're not already connected
    if (this->adjacencyList->count(vertex1) != 0 &&
        this->adjacencyList->count(vertex2) != 0 &&
        this->adjacencyList->at(vertex1).count(vertex2) == 0 &&
        this->adjacencyList->at(vertex2).count(vertex1) == 0)
    {
        this->adjacencyList->at(vertex1).insert(vertex2);
        this->adjacencyList->at(vertex2).insert(vertex1);
    }
}

template <typename T>
void Graph<T>::merge(const T &vertex1, const T &vertex2)
{
    // Exit if either vertex doesn't exist in this graph
    if (this->adjacencyList->count(vertex1) == 0 ||
        this->adjacencyList->count(vertex2) == 0)
    {
        return;
    }

    // Neighbors of v also have v as a neighbor. So to fix incoming edges we visit
    // each neighbor and replace vertex2 with vertex1 as their neighbor
    for (const T& neighbor : this->adjacencyList->at(vertex2))
    {
        if (neighbor != vertex1)
        {
            this->adjacencyList->at(neighbor).insert(vertex1);
            this->adjacencyList->at(neighbor).erase(vertex2);
        }
    }

    // To fix outgoing edges we combine the sets of neighbors of vertices 1 and 2
    this->adjacencyList->at(vertex1).merge(this->adjacencyList->at(vertex2));
    this->erase(vertex2);
}

template <typename T>
std::size_t Graph<T>::size() const
{
    return this->adjacencyList->size();
}

template <typename T>
DepthFirstIterator<T> Graph<T>::begin() const
{
    return DepthFirstIterator<T>(this->adjacencyList);
}

template <typename T>
DepthFirstIterator<T> Graph<T>::end() const
{
    return DepthFirstIterator<T>(nullptr);
}

template <typename T>
template <typename F>
const T *Graph<T>::findIf(F predicate) const
{
    for (const auto &[vertex, neighbors] : *this->adjacencyList)
    {
        if (predicate(vertex))
        {
            return &vertex;
        }
    }

    return nullptr;
}

#endif
