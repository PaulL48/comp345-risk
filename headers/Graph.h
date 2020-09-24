#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <ostream>
#include <type_traits>
#include "utilities.h"

template <class T, class M> 
M get_member_type(M T:: *);

template <typename T>
class DepthFirstIterator
{
public:
    using NeighborType = typename std::unordered_map<T, std::unordered_set<T>>::mapped_type;
    DepthFirstIterator(const std::unordered_map<T, std::unordered_set<T>>* adjacencyList);
    DepthFirstIterator(const DepthFirstIterator& dfi);
    ~DepthFirstIterator();
    DepthFirstIterator& operator=(const DepthFirstIterator& dfi);
    bool operator==(const DepthFirstIterator& dfi) const;
    bool operator!=(const DepthFirstIterator& dfi) const;
    DepthFirstIterator& operator++();
    const T& operator*() const;
    const T* operator->() const;
private:
    std::unordered_set<const NeighborType*>* visited;
    std::stack<const T*, std::vector<const T*>>* stack;

    // This is holding a pointer to the adjacency list
    // The motive for this is there is no implicit way to get
    // the neighbors of a neighbor. You must directly consult the adj list
    const std::unordered_map<T, std::unordered_set<T>>* adjacencyList;
};

template <typename T>
class Graph
{
public:
    using NeighborType = typename std::unordered_map<T, std::unordered_set<T>>::mapped_type;

    Graph();
    ~Graph();
    Graph(const Graph<T>& graph);
    Graph& operator=(const Graph<T>& graph);
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
    // The idea is that during map file parsing, particularly
    // creating the relations, we do
    // map.addEdgeIfContains(t1, t2)
    // for (Graph continent: continents)
    //      continent.addEdgeIfContains(t1, t2)
    void connect(const T& vertex1, const T& vertex2);

    DepthFirstIterator<T> begin() const;
    DepthFirstIterator<T> end() const;

    void erase(const T& vertex);
    //std::unordered_set<T> getKeys() const;
private:
    std::unordered_map<T, std::unordered_set<T>>* adjacencyList;
};

template <typename T>
Graph<T>::Graph() : adjacencyList(new std::unordered_map<T, std::unordered_set<T>>)
{
}

template <typename T>
Graph<T>::~Graph()
{
    delete this->adjacencyList;
}

template <typename T>
Graph<T>::Graph(const Graph<T>& graph) : adjacencyList(new std::unordered_map<T, std::unordered_set<T>>)
{
    *(this->adjacencyList) = *graph.adjacencyList;
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& graph)
{
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
    std::unordered_set<T> vertices = getKeys(*this->adjacencyList);
    std::unordered_set<T> reachableVertices;
    for (const T& vertex: *this)
    {
        reachableVertices.insert(vertex);
    }

    return reachableVertices == vertices;
}


template <typename T>
bool Graph<T>::isSubgraphOf(const Graph<T>& graph) const
{
    std::unordered_set<T> subgraphVertices = getKeys(*this->adjacencyList);
    std::unordered_set<T> graphVertices = getKeys(*graph.adjacencyList);

    if (!isSubset(graphVertices, subgraphVertices))
    {
        return false;
    }

    std::unordered_set<T> missingVertices = setDifference(graphVertices, subgraphVertices);
    Graph<T> destructuredGraph = graph;

    for (const T& vertex : missingVertices)
    {
        destructuredGraph.erase(vertex);
    }

    return *this == destructuredGraph;
}

template <typename T>
void Graph<T>::insert(const T& vertex)
{
    if (this->adjacencyList->count(vertex) == 0)
    {
        Graph<T>::NeighborType neighbors; // Default construct neighbor type
        this->adjacencyList->insert(std::make_pair(vertex, neighbors));
    }
}

template <typename T>
void Graph<T>::erase(const T& vertex)
{
    // First pass removes the vertex
    for (auto it = this->adjacencyList->begin(); it != this->adjacencyList->end();)
    {
        if (it->first == vertex)
        {
            it = this->adjacencyList->erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Second pass removes the edges to the vertex
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

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const std::unordered_map<T, std::unordered_set<T>>* adjacencyList) : visited(new std::unordered_set<const DepthFirstIterator<T>::NeighborType *>()),
                                                                                                        stack(new std::stack<const T*, std::vector<const T*>>()),
                                                                                                        adjacencyList(adjacencyList)
{
    if (adjacencyList != nullptr)
    {
        this->stack->push(&(this->adjacencyList->begin()->first));
    }
}

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(const DepthFirstIterator &dfi) : visited(new std::unordered_set<const DepthFirstIterator<T>::NeighborType *>()),
                                                                           stack(new std::stack<const T *, std::vector<const T *>>())
{
    this->adjacencyList = dfi.adjacencyList;
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
DepthFirstIterator<T>::~DepthFirstIterator()
{
    delete this->visited;
    delete this->stack;
}

template <typename T>
DepthFirstIterator<T> &DepthFirstIterator<T>::operator=(const DepthFirstIterator<T> &dfi)
{
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
bool DepthFirstIterator<T>::operator==(const DepthFirstIterator<T> &dfi) const
{
    return this->adjacencyList == dfi.adjacencyList;
}

template <typename T>
bool DepthFirstIterator<T>::operator!=(const DepthFirstIterator<T> &dfi) const
{
    return !(*this == dfi);
}

template <typename T>
DepthFirstIterator<T> &DepthFirstIterator<T>::operator++()
{
    const T* current = this->stack->top();
    this->stack->pop();

    this->visited->insert(&(this->adjacencyList->at(*current)));
    for (const T& neighbor : this->adjacencyList->at(*current))
    {
        if (this->visited->count(&(this->adjacencyList->at(neighbor))) == 0)
        {
            this->stack->push(&neighbor);
        }
    }

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

#endif
