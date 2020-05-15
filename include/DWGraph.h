#ifndef DWGRAPH_H_INCLUDED
#define DWGRAPH_H_INCLUDED

#include <cstddef>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <utility>

#include "DUGraph.h"

class DWGraph {
public:
    typedef size_t node_t;
    typedef long long weight_t;
    static constexpr weight_t INF = 1000000000;
    struct Edge{
        node_t v;
        weight_t w;
        Edge(node_t v, weight_t w);
    };
private:
    std::list<node_t> nodes;
    std::unordered_map< node_t, std::list< Edge > > adj;
    void assert_integrity() const;
public:
    DWGraph();
    void addNode(node_t u);
    template<class iterator_t>
    void removeNodes(iterator_t it1, iterator_t it2);
    void addEdge(node_t u, node_t v, weight_t w);
    const std::list<node_t>& getNodes() const;
    const std::list<Edge>& getAdj(node_t u) const;
    explicit operator DUGraph() const;
};

template<class iterator_t>
void DWGraph::removeNodes(iterator_t it1, iterator_t it2){
    std::unordered_set<node_t> s(it1, it2);
    // Remove edges
    for(auto &Adj: adj){
        for(auto it = Adj.second.begin(); it != Adj.second.end(); ){
            if(s.count(it->v)) it = Adj.second.erase(it);
            else               ++it;
        }
    }
    // Remove from adj and nodes
    for(auto it = nodes.begin(); it != nodes.end(); ){
        if(s.count(*it)){
            adj.erase(*it);
            it = nodes.erase(it);
        } else {
            ++it;
        }
    }
    assert_integrity();
}

#endif //DWGRAPH_H_INCLUDED
