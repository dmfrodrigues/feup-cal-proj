#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"
#include "statistics.h"

/**
 * @brief Shortest Path Interface
 * 
 */
class ShortestPath {
public:
    /**
     * @brief Shortest Path object Destructor
     * 
     */
    virtual ~ShortestPath();

    /**
     * @brief Initializes the data members that are required for the algorithm's execution
     * 
     * @param G Directed Weighted Graph
     * @param s Starting Node
     * @param d Destination Node
     */
    virtual void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s, DWGraph::node_t d) = 0;

    /**
     * @brief Retrieve the Start Node
     * 
     * @return DWGraph::node_t Start Node
     */
    virtual DWGraph::node_t getStart() const = 0;

    /**
     * @brief Retrieve the Destination Node
     * 
     * @return DWGraph::node_t Destination Node
     */
    virtual DWGraph::node_t getDest () const = 0;

    /**
     * @brief Execute the algorithm
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Retrieves the node chosen prior to getting to node u
     * 
     * @param u Destination Node
     * @return DWGraph::node_t Last Node before getting to u
     */
    virtual DWGraph::node_t getPrev(DWGraph::node_t u) const = 0;

    /**
     * @brief Get the Path object
     * 
     * @return std::list<DWGraph::node_t> Sequence of nodes that describe the path from Node s to d
     */
    virtual std::list<DWGraph::node_t> getPath() const final;

    /**
     * @brief Retrieves the path weight between two specific nodes
     * 
     * @return DWGraph::weight_t Weight of the path between the two nodes
     */
    virtual DWGraph::weight_t getPathWeight() const = 0;

    /**
     * @brief Shortest Path Between every of the Nodes provided and any other Node
     * 
     */
    class FromOneMany;

    /**
     * @brief Retrieves the statistics object
     * 
     * @return statistics_t Stores the execution time of the algorithm
     */
    virtual statistics_t getStatistics() const = 0;

    /**
     * @brief           Checks if a specific node was marked as visited
     * 
     * @param u         Node to be checked
     * @return true     If the node has been already visited
     * @return false    Otherwise
     */
    virtual bool hasVisited(DWGraph::node_t u) const = 0;
};

class ShortestPath::FromOneMany : public ShortestPath{
private:
    ShortestPathOneMany *oneMany = nullptr;
    const DWGraph::DWGraph *G = nullptr;
    DWGraph::node_t s, d;
public:
    FromOneMany(ShortestPathOneMany *oneMany);
    virtual void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s, DWGraph::node_t d);
    virtual void run();
    virtual DWGraph::node_t getStart() const;
    virtual DWGraph::node_t getDest () const;
    virtual DWGraph::node_t getPrev(DWGraph::node_t u) const;
    virtual DWGraph::weight_t getPathWeight() const;
    virtual statistics_t getStatistics() const;
    virtual bool hasVisited(DWGraph::node_t u) const;
};

#endif //SHORTESTPATH_H_INCLUDED
