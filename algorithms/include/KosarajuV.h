#ifndef KOSARAJU_VARIANT_H_INCLUDED
#define KOSARAJU_VARIANT_H_INCLUDED

#include "SCCnode.h"
#include "Reachability.h"

/**
 * @brief Variant of Kosaraju algorithm
 * 
 */
class KosarajuV : public SCCnode{
private:
    const DUGraph *G;
    DUGraph::node_t s;
    Reachability *r;
    std::unordered_map<DUGraph::node_t, bool> isSCC;
public:
    /**
     * @brief Construct from Reachability instance
     * 
     * @param r 
     */
    KosarajuV(Reachability *r);

    /**
     * @brief Initializes data members that will be used in the algorithm's execution
     * 
     * @param G     Directed Unweighted Graph
     */
    void initialize(const DUGraph *G, DUGraph::node_t s);

    /**
     * @brief Execute the algorithm
     * 
     */
    void run();
    bool is_scc(DUGraph::node_t v) const;
};

#endif //KOSARAJU_VARIANT_H_INCLUDED
