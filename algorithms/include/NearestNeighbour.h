#ifndef NN_H_INCLUDED
#define NN_H_INCLUDED


#include "TravellingSalesman.h"

#include <unordered_set>

/**
 * @brief Nearest Neighbour algorithm
 * 
 */
class NearestNeighbour : public TravellingSalesman {
private:
    const std::list<DWGraph::node_t> *nodes = nullptr;
    DWGraph::node_t s;
    weight_function *w = nullptr;
    std::list<DWGraph::node_t> path;
    std::unordered_multiset<DWGraph::node_t> visited, unvisited;
    statistics_t stats;
    
    /**
     * @brief Retrieves closest node to u
     * 
     * @param u                 Node to Use
     * @return DWGraph::node_t  Closest Node
     */
    DWGraph::node_t findClosest(DWGraph::node_t u);
public:
    /**
     * @brief Construct without arguments
     * 
     */
    NearestNeighbour();

    /**
     * @brief Initializes data members such as the starting node that are required for the algorithm's execution
     * 
     * @param nodes     List of the graph's nodes over which the algorithm will operate
     * @param s         Starting node
     * @param w         weight_function instance
     */
    void initialize(const std::list<DWGraph::node_t> *nodes, DWGraph::node_t s, weight_function *w);

    /**
     * @brief Executes the algorithm, generating a route
     * 
     */
    void run();

    /**
     * @brief Retrieves the route (sequence of nodes)
     * 
     * @return std::list<DWGraph::node_t> Sequence of nodes that characterize the route 
     */
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //NN_H_INCLUDED