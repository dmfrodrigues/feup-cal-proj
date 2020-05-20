#include "DFS.h"

void DFS::initialize(const DUGraph *G_, DUGraph::node_t s_){
    this->G = G_;
    this->s = s_;
    R.clear();
    for (DUGraph::node_t x : G->getNodes()) R[x] = false;
}

void DFS::dfs(DUGraph::node_t u){
    if(R[u]) return;
    R[u] = true;
    for(const DUGraph::node_t &v:G->getAdj(u))
        dfs(v);
}

void DFS::run(){
    dfs(s);
}

bool DFS::is_reachable(DUGraph::node_t v) const{
    return R.at(v);
}
