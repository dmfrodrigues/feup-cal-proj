#ifndef TARJAN_H_INCLUDED
#define TARJAN_H_INCLUDED

#include "SCC.h"
#include <bits/stdc++.h> 

class Tarjan : public SCC{
private:
    const DUGraph *G;
    int nid; //=1
    std::unordered_map<DUGraph::node_t, DUGraph::node_t> id;
    std::unordered_map<DUGraph::node_t, DUGraph::node_t> low;
    std::unordered_set<DUGraph::node_t> onStack;
    std::stack<DUGraph::node_t> L;
    std::unordered_map<DUGraph::node_t, DUGraph::node_t> SCCs;
public:
    Tarjan();
    void initialize(const DUGraph *G_);
    void DFS_T(DUGraph::node_t u);
    void run();
    DUGraph::node_t get_scc(DUGraph::node_t u) const;
};

#endif //TARJAN_H_INCLUDED
