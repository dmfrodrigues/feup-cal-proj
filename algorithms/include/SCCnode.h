#ifndef SCC_NODE_H_INCLUDED
#define SCC_NODE_H_INCLUDED

#include "DUGraph.h"

/**
 * @brief Strongly Connected Component node Interface
 * 
 */
class SCCnode{
public:
    /**
     * @brief SCCnode object destructor
     * 
     */
    virtual ~SCCnode();

    /**
     * @brief Initializes data members that are required for the algorithm's execution
     * 
     * @param G     Directed Unweighted Graph
     * @param s     Starting Node
     */
    virtual void initialize(const DUGraph *G, DUGraph::node_t s) = 0;

    /**
     * @brief Executes algorithm
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Checks if a node belongs to a Strongly Connected Component
     * 
     * @param v         Node to be checked
     * @return true     If it belongs to a SCC
     * @return false    Otherwise
     */
    virtual bool is_scc(DUGraph::node_t v) const = 0;
};

#endif //SCC_NODE_H_INCLUDED
