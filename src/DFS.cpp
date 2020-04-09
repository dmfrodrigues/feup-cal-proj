#include "DFS.h"

void DFS::initialize(const DUGraph *G, DUGraph::node_t s){
    this->G = G;
    this->s = s;
}

void DFS::dfs(DUGraph::node_t u){
    if(R[u]) return;
    R[u] = true;
    for(const auto &v:G->Adj(u))
        dfs(v);
}

void DFS::run(){
    dfs(s);
}

bool DFS::is_reachable(DUGraph::node_t v) const{
    return R[v];
}
