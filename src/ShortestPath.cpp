#include "ShortestPath.h"

typedef DWGraph::node_t     node_t;
typedef DWGraph::weight_t   weight_t;

std::list<node_t> ShortestPath::getPath() const{
    std::list<node_t> res;
    node_t d = getDest();
    while(d != getStart()){
        res.push_front(d);
        d = getPrev(d);
    }
    res.push_front(d);
    return res;
}

ShortestPath::FromOneMany::FromOneMany(ShortestPathOneMany *oneMany){
    this->oneMany = oneMany;
}

void ShortestPath::FromOneMany::initialize(const DWGraph *G, node_t s, node_t d){
    this->G = G;
    this->s = s;
    this->d = d;
    oneMany->initialize(G, s);
}
void ShortestPath::FromOneMany::run(){
    oneMany->run();
}

node_t ShortestPath::FromOneMany::getStart() const{
    return s;
}

node_t ShortestPath::FromOneMany::getDest() const{
    return d;
}

node_t ShortestPath::FromOneMany::getPrev(node_t u) const {
    return oneMany->getPrev(u);
}

weight_t ShortestPath::FromOneMany::getPathWeight() const {
    return oneMany->getPathWeight(d);
}
