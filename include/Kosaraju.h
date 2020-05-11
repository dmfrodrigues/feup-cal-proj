#ifndef KOSARAJU_H_INCLUDED
#define KOSARAJU_H_INCLUDED

#include "SCC.h"
#include <bits/stdc++.h> 

class Kosaraju : public SCC{
private:
    const DUGraph *G;
    std::unordered_set<DUGraph::node_t> S;
    std::stack<DUGraph::node_t> L;
    std::unordered_map<DUGraph::node_t, DUGraph::node_t> SCCs;
public:
    Kosaraju();
    void initialize(const DUGraph *G);
    void DFS_K(const DUGraph *G, DUGraph::node_t u);
    void assign(const DUGraph *G, DUGraph::node_t u, DUGraph::node_t root);
    void run();
    DUGraph::node_t get_scc(DUGraph::node_t v) const;
};

#endif //KOSARAJU_H_INCLUDED
