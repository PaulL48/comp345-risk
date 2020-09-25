#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <ostream>
#include <type_traits>

#include "SetUtilities.h"
#include "OutputUtilities.h"

template <typename T>
using AdjacencyList = std::unordered_map<T, std::unordered_set<T>>;

template <typename T>
using NeighborList = typename AdjacencyList<T>::mapped_type;

template <typename T>
class DepthFirstIterator
{
public:
    // Constructor
    DepthFirstIterator(const AdjacencyList<T>* adjacencyList);

    // Copy constructor
    DepthFirstIterator(const DepthFirstIterator& dfi);

    // Destructor
    ~DepthFirstIterator();

    // Copy assignment
    DepthFirstIterator& operator=(const DepthFirstIterator& dfi);

    // Return whether two DFS iterators are at the same point in iteration on the same adjacency list
    bool operator==(const DepthFirstIterator& dfi) const;

    // Return the negation of operator==
    bool operator!=(const DepthFirstIterator& dfi) const;

    // Advance the iterator to the next vertex
    DepthFirstIterator& operator++();

    // Get the vertex the iterator is currently indexing
    const T& operator*() const;

    // Get the vertex the iterator is currently indexing
    const T* operator->() const;

    // TODO: Add stream output
    template <typename U>
    friend std::ostream& operator<<(std::ostream& output, const DepthFirstIterator<U>& dfi);
private:
    // Tracks vertexes already visited. 
    // Improves performance and prevents cyclic graphs looping infinitely
    std::unordered_set<const NeighborList<T>*>* visited;

    // Track upcoming nodes during iteration
    std::stack<const T*, std::vector<const T*>>* stack;

    // Non-owning pointer to adjacency list. Used to get the neighbors of a neighbor
    const AdjacencyList<T>* adjacencyList;
};

template <typename T>
class Graph
{
public:
    // Default constructor
    Graph();

    // Copy constructor
    Graph(const Graph<T>& graph);

    // Destructor
    ~Graph();
    
    // Copy assignment
    Graph& operator=(const Graph<T>& graph);

    // Return whether two graphs are identical
    bool operator==(const Graph<T>& graph) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Graph<U>& graph);

    // Return whether this graph is a connected graph
    bool isConnected() const;

    // Return whether this graph is a subgraph of the supplied graph
    bool isSubgraphOf(const Graph<T>& graph) const;    

    // Insert the vertex into the graph if it is not already present
    void insert(const T& vertex);

    // Connect two vertices if both vertices exist
    void connect(const T& vertex1, const T& vertex2);

    // Remove the vertex and all edges to it from the graph
    void erase(const T& vertex);

    // Return iterator to the start of the container
    DepthFirstIterator<T> begin() const;

    // Return iterator past the end of the container
    DepthFirstIterator<T> end() const;

private:
    // Owning pointer to adjacency list
    AdjacencyList<T>* adjacencyList;
};

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
Graph<T>::Graph(const Graph<T>& graph) : adjacencyList(new AdjacencyList<T>())
{
    *(this->adjacencyList) = *graph.adjacencyList;
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& graph)
{
    // Pass the work on to the copy assignment of the member
    *(this->adjacencyList) = *graph.adjacencyList;
    return *this;
}

template <typename T>
bool Graph<T>::operator==(const Graph<T>& graph) const
{
    return *this->adjacencyList == *graph.adjacencyList;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const Graph<T>& graph)
{
    output << *graph.adjacencyList;
    return output;
}

template <typename T>
bool Graph<T>::isConnected() const
{
    // Get all the vertices directly from the adjacency list
    std::unordered_set<T> vertices = getKeys(*this->adjacencyList);
    
    // Traverse the graph using DFS
    std::unordered_set<T> reachableVertices;
    for (const T& vertex: *this)
    {
        reachableVertices.insert(vertex);
    }

    // If all the vertices are reachable, it is a connected graph
    return reachableVertices == vertices;
}


template <typename T>
bool Graph<T>::isSubgraphOf(const Graph<T>& graph) const
{
    // Algorithm Description:
    // A list of vertices is obtained via the set difference graph.vertices - thisGraph.vertices
    // The supplied graph is transformed by removing those vertices and connections to those vertices
    // If the transformed graph is equivalent to this graph, this graph is a subgraph

    std::unordered_set<T> subgraphVertices = getKeys(*this->adjacencyList);
    std::unordered_set<T> graphVertices = getKeys(*graph.adjacencyList);

    // Early test: If the vertices of this graph are not a subset of the supplied graph,
    // This graph cannot be a subgraph
    if (!isSubset(graphVertices, subgraphVertices))
    {
        return false;
    }

    std::unordered_set<T> missingVertices = setDifference(graphVertices, subgraphVertices);
    Graph<T> transformedGraph = graph;
    for (const T& vertex : missingVertices)
    {
        transformedGraph.erase(vertex);
    }

    return *this == transformedGraph;
}

template <typename T>
void Graph<T>::insert(const T& vertex)
{
    if (this->adjacencyList->count(vertex) == 0)
    {
        this->adjacencyList->insert(std::make_pair(vertex, NeighborList<T>()));
    }
}

template <typename T>
void Graph<T>::erase(const T& vertex)
{
    // Remove the vertex if it exists
    if (this->adjacencyList->count(vertex) != 0)
    {
        this->adjacencyList->erase(vertex);
    }
    

    // Remove all edges to the vertex
    for (auto & [vertexKey, neighbors] : *this->adjacencyList)
    {
        if (neighbors.count(vertex) != 0)
        {
            neighbors.erase(vertex);
        }
    }
}

template <typename T>
void Graph<T>::connect(const T& vertex1, const T& vertex2)
{
    if (this->adjacencyList->count(vertex1) != 0 && this->adjacencyList->count(vertex2) != 0)
    {
        this->adjacencyList->at(vertex1).insert(vertex2);
    }
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

//============================================================================================================================================================
// TEMPLATE CLASS DEFINITIONS: DepthFirstIterator
//============================================================================================================================================================

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const AdjacencyList<T>* adjacencyList) : visited(new std::unordered_set<const NeighborList<T>*>()),
                                                                                   stack(new std::stack<const T*, std::vector<const T*>>()),
                                                                                   adjacencyList(adjacencyList)
{
    if (adjacencyList != nullptr)
    {
        // The first vertex of the graph is pushed to the stack to start the depth first traversal
        this->stack->push(&(this->adjacencyList->begin()->first));
    }
}

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const DepthFirstIterator &dfi) : visited(new std::unordered_set<const NeighborList<T> *>()),
                                                                           stack(new std::stack<const T *, std::vector<const T *>>())
{
    this->adjacencyList = dfi.adjacencyList; // Non-owning pointer can be trivially copied from incoming iterator
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
DepthFirstIterator<T>::~DepthFirstIterator()
{
    // Non-owning pointer this->adjacencyList is not deleted
    delete this->visited;
    delete this->stack;
}

template <typename T>
DepthFirstIterator<T> &DepthFirstIterator<T>::operator=(const DepthFirstIterator<T> &dfi)
{
    this->adjacencyList = dfi.adjacencyList; // Non-owning pointer can be trivially copied from incoming iterator
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
bool DepthFirstIterator<T>::operator==(const DepthFirstIterator<T> &dfi) const
{
    // Equivalence is defined by two iterators being at the same point of iteration over the same adjacency list
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
    const T* current = this->stack->top();
    this->stack->pop();

    // Mark the current vertex as visited
    this->visited->insert(&(this->adjacencyList->at(*current)));

    // Push the current vertex's neighbors onto the stack if they haven't been visited
    for (const T& neighbor : this->adjacencyList->at(*current))
    {
        if (this->visited->count(&(this->adjacencyList->at(neighbor))) == 0)
        {
            this->stack->push(&neighbor);
        }
    }

    // Set the sentinel value of the pointer to become equivalent to Graph<T>::end()
    if (this->stack->empty())
    {
        this->adjacencyList = nullptr;
        return *this;
    }

    return *this;
}

template <typename T>
const T& DepthFirstIterator<T>::operator*() const
{
    return *(this->stack->top());
}

template <typename T>
const T* DepthFirstIterator<T>::operator->() const
{
    return this->stack->top();
}

template <typename T>
std::ostream& operator<<(std::ostream& output, const DepthFirstIterator<T>& dfi)
{
    output << "{" << std::endl;
    output << "\t" << "visited: " << *dfi.visited << std::endl;
    output << "\t" << "stack: " << *dfi.stack << std::endl;
    output << "\t" << "graph: " << *dfi.adjacencyList << std::endl;
    output << "}" << std::endl;
    return output;
}

#endif
