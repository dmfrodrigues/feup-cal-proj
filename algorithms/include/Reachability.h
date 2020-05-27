#ifndef REACHABILITY_H_INCLUDED
#define REACHABILITY_H_INCLUDED

#include "DUGraph.h"

/**
 * @brief Reachability (if a Node can or not be reached from another Node) Interface 
 * 
 */
class Reachability{
public:
    virtual ~Reachability();
    
    /**
     * @brief Initializes the Directed Unweighted Graph and the starting data members required by the algorithm
     * 
     * @param G     Directed Unweighted Graph
     * @param s     Starting Node
     */
    virtual void initialize(const DUGraph *G, DUGraph::node_t s) = 0;

    /**
     * @brief Executes the algorithm
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Retrieves the boolean value correspondent to the reachability of a Node (starting at Node s)
     * 
     * @param v         Node to Test
     * @return true     If it can be reached
     * @return false    Otherwise
     */
    virtual bool is_reachable(DUGraph::node_t v) const = 0;
};

#endif //REACHABILITY_H_INCLUDED
