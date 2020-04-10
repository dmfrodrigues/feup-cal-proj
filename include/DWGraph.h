#ifndef DWGRAPH_H_INCLUDED
#define DWGRAPH_H_INCLUDED

#include <cstddef>
#include <vector>
#include <list>
#include <utility>

class DWGraph {
public:
    typedef size_t node_t;
    typedef double weight_t;
private:
    std::vector< std::list< std::pair<node_t, weight_t> > > Adjacent;
public:
    DWGraph(node_t V);
    size_t getV() const;
    void addEdge(node_t u, node_t v, weight_t w);
    const std::list< std::pair<node_t, weight_t> >& Adj(node_t u) const;
};

#endif //DWGRAPH_H_INCLUDED
