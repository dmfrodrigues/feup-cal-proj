#ifndef SHORTESTPATHFROMONEMANY_H_INCLUDED
#define SHORTESTPATHFROMONEMANY_H_INCLUDED

#include "ShortestPath.h"

#include <unordered_map>

template<class T>
class ShortestPathFromOneMany : public ShortestPath {
private:
    const DWGraph *G;
    std::unordered_map<DWGraph::node_t, T> oneManys;
public:
    void initialize(const DWGraph *G);
    void run();
    std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const;
};

template<class T>
void ShortestPathFromOneMany<T>::initialize(const DWGraph *G){
    this->G = G;
    oneManys.clear();
    for(const node_t &u: G->getNodes()){
        oneManys[u] = T();
        oneManys[u].initialize(G, u);
    }
}

template<class T>
void ShortestPathFromOneMany::run(){
    for(const node_t &s: G->getNodes()){
        dijkstra[s].run();
    }
}

template<class T>
std::list<node_t> ShortestPathFromOneMany<T>::getPath(node_t s, node_t d) const{
    return oneManys.at(s).getPath(d);
}

template<class T>
weight_t ShortestPathFromOneMany<T>::getPathWeight(node_t s, node_t d) const{
    return oneManys.at(s).getPathWeight(d);
}

#endif //SHORTESTPATHFROMONEMANY_H_INCLUDED
