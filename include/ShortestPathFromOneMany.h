#ifndef SHORTESTPATHALLFROMONEMANY_H_INCLUDED
#define SHORTESTPATHALLFROMONEMANY_H_INCLUDED

#include "ShortestPathAll.h"

#include <unordered_map>

template<class T>
class ShortestPathAllFromOneMany : public ShortestPathAll {
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
void ShortestPathAllFromOneMany<T>::initialize(const DWGraph *G){
    this->G = G;
    oneManys.clear();
    for(const DWGraph::node_t &u: G->getNodes()){
        oneManys[u] = T();
        oneManys[u].initialize(G, u);
    }
}

template<class T>
void ShortestPathAllFromOneMany<T>::run(){
    for(const DWGraph::node_t &s: G->getNodes()){
        oneManys[s].run();
    }
}

template<class T>
std::list<DWGraph::node_t> ShortestPathAllFromOneMany<T>::getPath(DWGraph::node_t s, DWGraph::node_t d) const{
    return oneManys.at(s).getPath(d);
}

template<class T>
DWGraph::weight_t ShortestPathAllFromOneMany<T>::getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const{
    return oneManys.at(s).getPathWeight(d);
}

#endif //SHORTESTPATHALLFROMONEMANY_H_INCLUDED
