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
class DepthFirstIterator
{
public:
    using NeighborType = typename std::unordered_map<T, std::vector<T>>::mapped_type;
    DepthFirstIterator(std::unordered_map<T, std::vector<T>>* adjacencyList);
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
    std::unordered_map<T, std::vector<T>>* adjacencyList;
};

template <typename T>
class Graph
{
public:
    using NeighborType = typename std::unordered_map<T, std::vector<T>>::mapped_type;

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

    DepthFirstIterator<T> begin();
    DepthFirstIterator<T> end();
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

template <typename T>
DepthFirstIterator<T> Graph<T>::begin()
{
    return DepthFirstIterator<T>(this->adjacencyList);
}


template <typename T>
DepthFirstIterator<T> Graph<T>::end()
{
    return DepthFirstIterator<T>(nullptr);
}

template <typename T>
DepthFirstIterator<T>::DepthFirstIterator(std::unordered_map<T, std::vector<T>>* adjacencyList) : visited(new std::unordered_set<const DepthFirstIterator<T>::NeighborType *>()),
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
    for (T& neighbor : this->adjacencyList->at(*current))
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
