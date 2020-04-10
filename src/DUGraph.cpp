#include "DUGraph.h"

DUGraph::DUGraph(DUGraph::node_t V): Adjacent(V){}

size_t DUGraph::getV() const{
    return Adjacent.size();
}

void DUGraph::addEdge(DUGraph::node_t u, DUGraph::node_t v){
    Adjacent[u].push_back(v);
}

const std::list<DUGraph::node_t>& DUGraph::Adj(DUGraph::node_t u) const{
    return Adjacent[u];
}
