#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include "Reachability.h"

class DFS : public Reachability {
private:
    const DUGraph *G;
    DUGraph::node_t s;
    std::vector<bool> R;
    
    void dfs(DUGraph::node_t u);
public:
    void initialize(const DUGraph *G, DUGraph::node_t s);
    void run();
    bool is_reachable(DUGraph::node_t v) const;
};

#endif //DFS_H_INCLUDED
