#ifndef SHORTESTPATHALL_H_INCLUDED
#define SHORTESTPATHALL_H_INCLUDED

#include <list>
#include <vector>
#include <queue>
#include <thread>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"
#include "shared_queue.h"

/**
 * @brief Shortest Path Between Each Pair of Vertices
 * 
 */
class ShortestPathAll {
public:
    /**
     * @brief Initializes the data members that are required for the algorithm's execution such as the G graph
     * 
     * @param G Directed Weighted Graph
     */
    virtual void initialize(const DWGraph::DWGraph *G) = 0;

    /**
     * @brief Executes the algorithm generating two 2D vector on with the distance between any pair of nodes and the other with (????)
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Retrieves the node chosen prior to getting to node d from s
     * 
     * @param s                     Starting Node
     * @param d                     Destination Node
     * @return DWGraph::node_t      Last Node before getting to the destination Node
     */
    virtual DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const = 0;

    /**
     * @brief Retrieves the sequence of nodes of the path starting at node s and ending at d
     * 
     * @param s                             Starting Node
     * @param d                             Destination Node
     * @return std::list<DWGraph::node_t>   Sequence of nodes that describe the path from Node s to d
     */
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const final;

    /**
     * @brief Retrieves the path weight between node s and d
     * 
     * @param s                     Starting Node
     * @param d                     Destination Node
     * @return DWGraph::weight_t    Weight of the path between the two nodes
     */
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const = 0;

    /**
     * @brief Retrieves the statistics object
     * 
     * @return statistics_t Stores the execution time of the algorithm
     */
    virtual statistics_t getStatistics() const = 0;

    /**
     * @brief Shortest Path Between every of the Nodes provided and any other Node
     * 
     */
    class FromOneMany;
};


class ShortestPathAll::FromOneMany : public ShortestPathAll {
private:
    size_t nthreads;
    shared_queue<DWGraph::node_t> Q;
    std::vector< std::thread > threads;
    const ShortestPathOneMany *oneMany;
    std::unordered_map<DWGraph::node_t, ShortestPathOneMany*> oneManys;
    const DWGraph::DWGraph *G = nullptr;
    statistics_t stats;

    /**
     * @brief Function to be executed by a thread
     * 
     * @param p Shortest Path All Object
     */
    static void thread_func(ShortestPathAll::FromOneMany *p);
public:
    /**
     * @brief Constructor
     * 
     * @param oneMany  Method of Shortest Path One Many to Use
     * @param nthreads Number of Threads to Use
     */
    FromOneMany(ShortestPathOneMany *oneMany, size_t nthreads);

    /**
     * @brief Initializes the graph data member G and the set of nodes to be used as sources
     * 
     * @param G 
     * @param nodes 
     */
    void initialize(const DWGraph::DWGraph *G, const std::unordered_set<DWGraph::node_t> &nodes);
    
    /**
     * @brief Initializes the graph data member G 
     * 
     * @param G Directed Weighted Graph
     */
    void initialize(const DWGraph::DWGraph *G);

    /**
     * @brief Executes the algorithm computing paths for pairs of vertices
     * 
     */
    void run();

    /**
     * @brief Retrieves the node chosen prior to getting to node d from s
     * 
     * @param s                     Starting Node
     * @param d                     Destination Node
     * @return DWGraph::node_t      Last Node before getting to the destination Node
     */
    DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const;

    /**
     * @brief Retrieves the path weight between node s and d
     * 
     * @param s                     Starting Node
     * @param d                     Destination Node
     * @return DWGraph::weight_t    Weight of the path between the two nodes
     */
    DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const;

    /**
     * @brief Retrieves the statistics object
     * 
     * @return statistics_t Stores the execution time of the algorithm
     */
    statistics_t getStatistics() const;
};

#endif //SHORTESTPATHALL_H_INCLUDED
