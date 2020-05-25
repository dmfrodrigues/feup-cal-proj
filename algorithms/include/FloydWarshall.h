#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "ShortestPathAll.h"
#include "DWGraph.h"

#include <vector>

/**
 * @brief Floyd-Warshall algorithm
 * 
 */
class FloydWarshall: public ShortestPathAll {
private:
    const DWGraph::DWGraph *G;
    typedef size_t id_t;
    std::unordered_map<DWGraph::node_t, id_t> node2id;
    std::unordered_map<id_t, DWGraph::node_t> id2node;
    std::vector< std::vector<DWGraph::weight_t> > dist;
    std::vector< std::vector<DWGraph::node_t  > > prev;
    statistics_t stats;
public:
    /**
     * @brief Construct without arguments
     * 
     */
    FloydWarshall();

    /**
     * @brief Initializes the data members that are required for the algorithm's execution such as the G graph
     * 
     * @param G Directed Weighted Graph
     */
    void initialize(const DWGraph::DWGraph *G);

    /**
     * @brief Executes the algorithm
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
    DWGraph::weight_t getPathWeight(DWGraph::node_t u, DWGraph::node_t v) const;
    statistics_t getStatistics() const;
};

#endif //FLOYDWARSHALL_H_INCLUDED