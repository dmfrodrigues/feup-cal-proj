#include "Kosaraju.h"
#include <iostream>

typedef DUGraph::node_t node_t;

Kosaraju::Kosaraju(){}

void Kosaraju::initialize(const DUGraph *G){
    this->G = G;
    S.clear();
    SCCs.clear();
}

void Kosaraju::DFS_K(const DUGraph *G, DUGraph::node_t u){
    if (S.find(u) != S.end()) return;
    S.insert(u);
    for (node_t v : G->getAdj(u)) DFS_K(G,v);
    L.push(u);
}

void Kosaraju::assign(const DUGraph *G, DUGraph::node_t u, DUGraph::node_t root){
    if (SCCs.find(u) != SCCs.end()) return;
    std::cout << "HEHERH   " << u << std::endl;
    SCCs[u] = root;
    for (node_t v : G->getTranspose().getAdj(u)) assign(G, v, root);
}

void Kosaraju::run(){
    for (node_t u : G->getNodes()) DFS_K(G,u);
    while(!L.empty()){
        node_t u = L.top();
        assign(G,u,u);
        L.pop();
    }
    
}

node_t Kosaraju::get_scc(node_t u) const{
    return SCCs.at(u);
}
