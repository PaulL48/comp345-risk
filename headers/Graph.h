#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <ostream>
#include <type_traits>

template <class T, class M> 
M get_member_type(M T:: *);

template <typename T>
class Graph
{
public:
    using NeighborType = typename std::remove_pointer<decltype(get_member_type(&Graph<T>::adjacencyList))>::type::mapped_type;

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

    class DepthFirstIterator
    {
    public:
        using NeighborType = typename std::remove_pointer<decltype(get_member_type(&Graph<T>::adjacencyList))>::type::mapped_type;
        DepthFirstIterator(std::unordered_map<T, std::vector<T>>* adjacencyList);
        DepthFirstIterator(const DepthFirstIterator& dfi);
        ~DepthFirstIterator();
        DepthFirstIterator& operator=(const DepthFirstIterator& dfi);
        bool operator==(const DepthFirstIterator& dfi) const;
        bool operator!=(const DepthFirstIterator& dfi) const;
        DepthFirstIterator& operator++();
        T& operator*() const;
        T* operator->() const;
    private:
        std::unordered_set<const NeighborType*>* visited;
        std::stack<T*, std::vector<const T*>>* stack;

        // This is holding a pointer to the adjacency list
        // The motive for this is there is no implicit way to get
        // the neighbors of a neighbor. You must directly consult the adj list
        std::unordered_map<T, std::vector<T>>* adjacencyList;
    };

    DepthFirstIterator begin();
    DepthFirstIterator end();

    friend DepthFirstIterator;
private:
    std::unordered_map<T, std::vector<T>>* adjacencyList;
};

template <typename T>
Graph<T>::Graph() : adjacencyList(new std::unordered_map<T, std::vector<T>>)
{
}

template <typename T>
Graph<T>::~Graph()
{
    delete this->adjacencyList;
}

template <typename T>
Graph<T>::Graph(const Graph<T>& graph) : adjacencyList(new std::unordered_map<T, std::vector<T>>)
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
std::ostream& operator<<(std::ostream& output, const Graph<T>& graph)
{
    return output;
}

template <typename T>
bool Graph<T>::isConnected() const
{
    
    return false;
}

template <typename T>
bool Graph<T>::isSubgraphOf(const Graph<T>& graph) const
{
    return false;
}

template <typename T>
void Graph<T>::insert(const T& vertex)
{
    if (this->adjacencyList->count(vertex) == 0)
    {
        Graph<T>::NeighborType neighbors;
        this->adjacencyList->insert(std::make_pair(vertex, neighbors));
    }
}

template <typename T>
void Graph<T>::connect(const T& vertex1, const T& vertex2)
{
    if (this->adjacencyList->count(vertex1) != 0 && this->adjacencyList->count(vertex2) != 0)
    {
        this->adjacencyList->at(vertex1).push_back(vertex2);
        this->adjacencyList->at(vertex1).push_back(vertex1);
    }
}

#include <iostream>

template <typename T>
void Graph<T>::iter_dfs()
{
    std::cout << "Starting DFS" << std::endl;
    if (this->adjacencyList->empty())
    {
        return;
    }

    // Instead of storing key addresses, we store value addresses
    // This gives O(1) lookups and uniqueness

    std::unordered_set<const Graph<T>::NeighborType*> visited;
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

template <typename T>
typename Graph<T>::DepthFirstIterator Graph<T>::begin()
{
    return DepthFirstIterator(this->adjacencyList);
}

template <typename T>
typename Graph<T>::DepthFirstIterator Graph<T>::end()
{
    return DepthFirstIterator(nullptr);
}

template <typename T>
Graph<T>::DepthFirstIterator::DepthFirstIterator(std::unordered_map<T, std::vector<T>>* adjacencyList) : adjacencyList(adjacencyList),
                                                                                                         visited(new std::unordered_set<const Graph<T>::NeighborType *>()),
                                                                                                         stack(new std::stack<const T *, std::vector<const T *>>())
{
    if (adjacencyList != nullptr)
    {
        this->stack->push(&(adjacencyList->begin()->first));
    }
}

template <typename T>
Graph<T>::DepthFirstIterator::DepthFirstIterator(const DepthFirstIterator &dfi) : visited(new std::unordered_set<const Graph<T>::NeighborType *>()),
                                                                                  stack(new std::stack<const T *, std::vector<const T *>>())
{
    this->adjacencyList = dfi.adjacencyList;
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
Graph<T>::DepthFirstIterator::~DepthFirstIterator()
{
    delete this->visited;
    delete this->stack;
}

template <typename T>
typename Graph<T>::DepthFirstIterator &Graph<T>::DepthFirstIterator::operator=(const DepthFirstIterator &dfi)
{
    *this->visited = *dfi.visited;
    *this->stack = *dfi.stack;
}

template <typename T>
bool Graph<T>::DepthFirstIterator::operator==(const DepthFirstIterator &dfi) const
{
    return *this->stack == *dfi.stack && *this->visited == *dfi.visited;
}

template <typename T>
bool Graph<T>::DepthFirstIterator::operator!=(const DepthFirstIterator &dfi) const
{
    return !(*this == dfi);
}

template <typename T>
typename Graph<T>::DepthFirstIterator &Graph<T>::DepthFirstIterator::operator++()
{
    const T* current = this->stack->top();
    this->stack->pop();

    if (this->visited->count(&(this->adjacencyList->at(*current))) != 0)
    {
        return *this;
    }

    this->visited->insert(&(this->adjacencyList->at(*current)));
    for (const T& neighbor : this->adjacencyList->at(*current))
    {
        if (this->visited->count(&(this->adjacencyList->at(neighbor))) == 0)
        {
            this->stack->push(&neighbor);
        }
    }

    return *this;
}

template <typename T>
T& Graph<T>::DepthFirstIterator::operator*() const
{
    // Derefencing at or past end iterator is UB
    return *(this->stack->top());
}

template <typename T>
T* Graph<T>::DepthFirstIterator::operator->() const
{
    return this->stack->top();
}

#endif
