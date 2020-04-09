#include "DWGraph.h"

DWGraph::DWGraph(DWGraph::node_t V): Adjacent(V){}

size_t DWGraph::getV() const{
    return Adjacent.size();
}

void DWGraph::addEdge(DWGraph::node_t u, DWGraph::node_t v, DWGraph::weight_t w){
    Adjacent[u].push_back(std::make_pair(v, w));
}

const std::list< std::pair<DWGraph::node_t, DWGraph::weight_t> >& DWGraph::Adj(DWGraph::node_t u) const{
    return Adjacent[u];
}
