#include "ShortestPath.h"

ShortestPath::FromOneMany::FromOneMany(ShortestPathOneMany *oneMany){
    this->oneMany = oneMany;
}

void ShortestPath::FromOneMany::initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d){
    this->G = G;
    this->s = s;
    this->d = d;
    oneMany->initialize(G, s);
}
void ShortestPath::FromOneMany::run(){
    oneMany->run();
}

std::list<DWGraph::node_t> ShortestPath::FromOneMany::getPath() const {
    return oneMany->getPath(d);
}

DWGraph::weight_t ShortestPath::FromOneMany::getPathWeight() const {
    return oneMany->getPathWeight(d);
}
