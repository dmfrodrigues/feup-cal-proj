#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include "Reachability.h"

/**
 * @brief Depth-first Search Algorithm
 * 
 */
class DFS : public Reachability {
private:
    const DUGraph *G;
    DUGraph::node_t s;
    std::unordered_map<DUGraph::node_t, bool> R;
    
    /**
     * @brief Executes the algorithm itself
     * 
     * @param u Node to consider as the Start/Root
     */
    void dfs(DUGraph::node_t u);
public:

    /**
     * @brief Initializes data members that are required for the algorithm's execution
     * 
     * @param G     Directed Unweighted Graph
     * @param s     Starting Node
     */
    void initialize(const DUGraph *G, DUGraph::node_t s);

    /**
     * @brief Computes for every Node if it can be reached starting at s (Starting Node data member)
     * 
     */
    void run();

    /**
     * @brief Retrieves the boolean value correspondent to the reachability of a Node (starting at Node s)
     * 
     * @param v         Node to Test
     * @return true     If it can be reached
     * @return false    Otherwise
     */
    bool is_reachable(DUGraph::node_t v) const;
};

#endif //DFS_H_INCLUDED
