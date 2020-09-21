#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <ostream>
#include <type_traits>


template<typename T>
class Graph
{
public:
    Graph();
    ~Graph();
    Graph(const Graph<T>& graph);
    Graph& operator=(const Graph<T>& graph);

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

    void iter_dfs();
private:
    std::unordered_map<T, std::vector<T>>* adjacencyList;
};

template<typename T>
Graph<T>::Graph() : adjacencyList(new std::unordered_map<T, std::vector<T>>)
{
}

template<typename T>
Graph<T>::~Graph()
{
    delete this->adjacencyList;
}

template<typename T>
Graph<T>::Graph(const Graph<T>& graph)
{
    *(this->adjacencyList) = *graph.adjacencyList;
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& graph)
{
    *(this->adjacencyList) = *graph.adjacencyList;
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Graph<T>& graph)
{
    return output;
}

template<typename T>
bool Graph<T>::isConnected() const
{
    return false;
}

template<typename T>
bool Graph<T>::isSubgraphOf(const Graph<T>& graph) const
{
    return false;
}

template<typename T>
void Graph<T>::insert(const T& vertex)
{
    if (this->adjacencyList->count(vertex) == 0)
    {
        typename std::remove_pointer<decltype(this->adjacencyList)>::type::mapped_type neighbors;
        this->adjacencyList->insert(std::make_pair(vertex, neighbors));
    }
}

template<typename T>
void Graph<T>::connect(const T& vertex1, const T& vertex2)
{
    if (this->adjacencyList->count(vertex1) != 0 && this->adjacencyList->count(vertex2) != 0)
    {
        this->adjacencyList->at(vertex1).push_back(vertex2);
    }
}

#include <iostream>

template<typename T>
void Graph<T>::iter_dfs()
{
    std::cout << "Starting DFS" << std::endl;
    if (this->adjacencyList->empty())
    {
        return;
    }

    // Instead of storing key addresses, we store value addresses
    // This gives O(1) lookups and uniqueness
    using mapped_type = typename std::remove_pointer<decltype(this->adjacencyList)>::type::mapped_type;
    std::unordered_set<const mapped_type*> visited;
    std::stack<const T*, std::vector<const T*>> stack;
    stack.push(&(this->adjacencyList->cbegin()->first));

    while (!stack.empty())
    {
        const T* current = stack.top();
        stack.pop();

        if (visited.count(&(this->adjacencyList->at(*current))) != 0)
        {
            continue;
        }

        visited.insert(&(this->adjacencyList->at(*current)));
        std::cout << "Node: " << *current << std::endl;

        for (const T& neighbor : this->adjacencyList->at(*current))
        {
            if (visited.count(&(this->adjacencyList->at(neighbor))) == 0)
            {
                stack.push(&neighbor);
            }
        }
    }
}

#endif
