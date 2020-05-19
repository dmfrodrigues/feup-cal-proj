#include "ShortestPathAll.h"

std::list<DWGraph::node_t> ShortestPathAll::getPath(DWGraph::node_t s, DWGraph::node_t d) const{
    std::list<DWGraph::node_t> res;
    while(d != s){
        res.push_front(d);
        d = getPrev(s, d);
    }
    res.push_front(d);
    return res;
}

ShortestPathAll::FromOneMany::FromOneMany(ShortestPathOneMany *oneMany_){
    this->oneMany = oneMany_;
}

void ShortestPathAll::FromOneMany::initialize(const DWGraph::DWGraph *G_){
    this->G = G_;
}

void ShortestPathAll::FromOneMany::run(){
    for(const DWGraph::node_t &s: G->getNodes()){
        oneMany->initialize(G, s);
        oneMany->run();
        for(const DWGraph::node_t &d: G->getNodes()){
            dist[s][d] = oneMany->getPathWeight(d);
            prev[s][d] = oneMany->getPrev(d);
        }
    }
}

DWGraph::node_t ShortestPathAll::FromOneMany::getPrev(DWGraph::node_t s, DWGraph::node_t d) const{
    return prev.at(s).at(d);
}

DWGraph::weight_t ShortestPathAll::FromOneMany::getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const{
    return dist.at(s).at(d);
}
