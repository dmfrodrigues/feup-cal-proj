#ifndef TRAVELLINGSALESMAN_H_INCLUDED
#define TRAVELLINGSALESMAN_H_INCLUDED

#include "DWGraph.h"
#include "statistics.h"
#include <chrono>

/**
 * @brief Travelling Salesman Interface.
 * 
 */
class TravellingSalesman{
public:
    /**
     * @brief Weight Function
     * 
     */
    class weight_function{
    public:
        virtual ~weight_function();
        /**
         * @brief Computes the cost (weight) of transitioning from node u to v after visiting all nodes of S
         * 
         * @param S                     List of already visited nodes
         * @param u                     Current node
         * @param v                     Node to reach (goal)
         * @return DWGraph::weight_t    Cost to get from u to v
         */
        virtual DWGraph::weight_t operator()(const std::unordered_set<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const = 0;
    };

    /**
     * @brief Travelling Salesman object destructor
     * 
     */
    virtual ~TravellingSalesman();

    /**
     * @brief Initializes data members such as the starting node that are required for the algorithm's execution
     * 
     * @param nodes     List of the graph's nodes over which the algorithm will operate
     * @param s         Starting node
     * @param w         weight_function instance
     */
    virtual void initialize(const std::list<DWGraph::node_t> *nodes, DWGraph::node_t s, weight_function *w) = 0;
    
    /**
     * @brief Executes the algorithm generating a route
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Retrieves the route (sequence of nodes)
     * 
     * @return std::list<DWGraph::node_t> Sequence of nodes that characterize the route 
     */
    virtual std::list<DWGraph::node_t> getTour() const = 0;

    /**
     * @brief Retrieves the statistics object
     * 
     * @return statistics_t Stores the execution time of the algorithm
     */
    virtual statistics_t getStatistics() const = 0;
};

#endif //TRAVELLINGSALESMAN_H_INCLUDED