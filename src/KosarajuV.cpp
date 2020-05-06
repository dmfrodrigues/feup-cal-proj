#include "KosarajuV.h"

typedef DUGraph::node_t node_t;

KosarajuV::KosarajuV(Reachability *r){
    this->r = r;
}

void KosarajuV::initialize(const DUGraph *G, node_t s){
    this->G = G;
    this->s = s;
    isSCC.clear();
}

void KosarajuV::run(){
    r->initialize(G, s);
    for(const node_t u: G->getNodes()){
        isSCC[u] = r->is_reachable(u);
    }
    DUGraph GT = G->getTranspose();
    r->initialize(&GT, s);
    for(const node_t u: G->getNodes()){
        isSCC[u] = isSCC[u] && r->is_reachable(u);
    }
}

bool KosarajuV::is_scc(node_t v) const{
    return isSCC.at(v);
}
