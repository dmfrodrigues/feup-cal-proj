#ifndef HELDKARP_H_INCLUDED
#define HELDKARP_H_INCLUDED

#include "TravellingSalesman.h"

#include <vector>

/**
 * @brief Held-Karp algorithm
 * 
 */
class HeldKarp : public TravellingSalesman {
private:
    typedef unsigned short id_t;
    static const id_t INVALID_ID;
    typedef unsigned long long set_t;
    template <class T> using state_struct = std::vector<std::vector<T> >;
    
    const weight_function *w = nullptr;
    id_t s = INVALID_ID;
    std::list<DWGraph::node_t> path;
    statistics_t stats;
    std::unordered_multimap<DWGraph::node_t, id_t> node2id;
    std::unordered_map<id_t, DWGraph::node_t> id2node;
    state_struct<DWGraph::weight_t> D;
    state_struct<std::pair<set_t, id_t> > P;

    DWGraph::weight_t w_wrapper(const set_t &S, id_t u, id_t v) const;
public:
    /**
     * @brief Construct without arguments
     * 
     */
    HeldKarp();

    /**
     * @brief Initializes data members such as the starting node that are required for the algorithm's execution
     * 
     * @param nodes     List of the graph's nodes over which the algorithm will operate
     * @param s         Starting node
     * @param w         weight_function instance
     */
    void initialize(const std::list<DWGraph::node_t> *nodes, DWGraph::node_t s, weight_function *w);
    
    /**
     * @brief Executes the algorithm
     * 
     */
    void run();

    /**
     * @brief Retrieves the minimum cost of reaching v after having visited all cities in S
     * 
     * @param S                     cities already visited
     * @param v                     destination
     * @return DWGraph::weight_t    cost
     */
    DWGraph::weight_t HK(const set_t &S, id_t v);
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //HELDKARP_H_INCLUDED
