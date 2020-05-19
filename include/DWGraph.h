#ifndef DWGRAPH_H_INCLUDED
#define DWGRAPH_H_INCLUDED

#include <cstddef>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <utility>

#include "DUGraph.h"

namespace DWGraph {
    typedef size_t node_t;
    typedef long long weight_t;
    static constexpr weight_t INF = 1000000000;
    struct Edge{
        node_t v;
        weight_t w;
        Edge(node_t v, weight_t w);
        bool operator<(const Edge &e) const{
            return v < e.v;
        }
    };
    class DWGraph {
    public:
        
    private:
        std::list<node_t> nodes;
        std::unordered_map< node_t, std::list< Edge > > adj;
        std::unordered_map< node_t, std::unordered_set< node_t> > pred;
        void assert_integrity() const;
    public:
        DWGraph();
        void addNode(node_t u);
        template<class iterator_t>
        void removeNodes(iterator_t it1, iterator_t it2);
        void removeNode(node_t u);
        bool hasNode(node_t u) const;
        void addEdge(node_t u, node_t v, weight_t w);
        const std::list<node_t>& getNodes() const;
        const std::list<Edge>& getAdj(node_t u) const;
        size_t getNumberEdges() const;
        DWGraph getTranspose() const;
        explicit operator DUGraph() const;
    };
}

template<class iterator_t>
void DWGraph::DWGraph::removeNodes(iterator_t it1, iterator_t it2){
    for(auto it = it1; it != it2; ++it)
        removeNode(*it);
}

#endif //DWGRAPH_H_INCLUDED
