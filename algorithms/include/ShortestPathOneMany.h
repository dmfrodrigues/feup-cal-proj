#ifndef SHORTESTPATHONEMANY_H_INCLUDED
#define SHORTESTPATHONEMANY_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "statistics.h"

/**
 * @brief Shortest Path From One Node to All other Nodes (Shortest Path One Many Interface)
 * 
 */
class ShortestPathOneMany {
private:

    /**
     * @brief Retrieve the Starting Node
     * 
     * @return DWGraph::node_t Starting Node
     */
    virtual DWGraph::node_t getStart() const = 0;
public:
    /**
     * @brief Shortest Path One Many object Destructor
     * 
     */
    virtual ~ShortestPathOneMany();

    /**
     * @brief Initializes the data members that are required for the algorithm's execution
     * 
     * @param G Directed Weighted Graph
     * @param s Starting Node
     */
    virtual void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s) = 0;

    /**
     * @brief Execute the algorithm
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Retrieves the node chosen prior to getting to node d
     * 
     * @param d                 Destination Node
     * @return DWGraph::node_t  Last Node before getting to the destination Node
     */
    virtual DWGraph::node_t getPrev(DWGraph::node_t d) const = 0;

    /**
     * @brief Get the Path object
     * 
     * @param d 
     * @return std::list<DWGraph::node_t> 
     */
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t d) const final;

    /**
     * @brief Retrieves the sequence of nodes of the path starting at node s and ending at d
     * 
     * @param d                     Destination Node
     * @return DWGraph::weight_t    Sequence of nodes that describe the path from Node s to d
     */
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t d) const = 0;

    /**
     * @brief Retrieves the statistics object
     * 
     * @return statistics_t Stores the execution time of the algorithm
     */
    virtual statistics_t getStatistics() const = 0;

    /**
     * @brief Checks if a specific node was marked as visited
     * 
     * @param u         Node to be checked
     * @return true     If the node has been already visited
     * @return false    Otherwise
     */
    virtual bool hasVisited(DWGraph::node_t u) const = 0;

    /**
     * @brief Clones the class instance
     * 
     * @return ShortestPathOneMany* new class instance
     */
    virtual ShortestPathOneMany* clone() const = 0;
};

#endif //SHORTESTPATHONEMANY_H_INCLUDED
