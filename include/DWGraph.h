#ifndef DWGRAPH_H_INCLUDED
#define DWGRAPH_H_INCLUDED

#include <cstddef>
#include <unordered_map>
#include <list>
#include <utility>

class DWGraph {
public:
    typedef size_t node_t;
    typedef double weight_t;
    static constexpr weight_t INF = 1000000000;
    struct Edge{
        node_t v;
        weight_t w;
        Edge(node_t v, weight_t w):v(v),w(w){}
    };
private:
    std::list<node_t> nodes;
    std::unordered_map< node_t, std::list< Edge > > adj;
public:
    DWGraph();
    void addNode(node_t u);
    void addEdge(node_t u, node_t v, weight_t w);
    const std::list<node_t>& getNodes() const;
    const std::list<Edge>& getAdj(node_t u) const;
};

#endif //DWGRAPH_H_INCLUDED
