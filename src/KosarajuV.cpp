#include "KosarajuV.h"

typedef DUGraph::node_t node_t;

KosarajuV::KosarajuV(Reachability *r_){
    this->r = r_;
}

void KosarajuV::initialize(const DUGraph *G_, node_t s_){
    this->G = G_;
    this->s = s_;
    this->isSCC.clear();
}

void KosarajuV::run(){
    r->initialize(G, s);
    r->run();
    for(const node_t u: G->getNodes()){
        isSCC[u] = r->is_reachable(u);
    }
    DUGraph GT = G->getTranspose();
    r->initialize(&GT, s);
    r->run();
    for(const node_t u: G->getNodes()){
        isSCC[u] = isSCC[u] && r->is_reachable(u);
    }
}

bool KosarajuV::is_scc(node_t v) const{
    return isSCC.at(v);
}
