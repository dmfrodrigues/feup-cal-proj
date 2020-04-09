#ifndef DUGRAPH_H_INCLUDED
#define DUGRAPH_H_INCLUDED

#include <cstddef>
#include <vector>
#include <list>

class DUGraph {
public:
    typedef size_t node_t;
private:
    std::vector< std::list<node_t> > Adjacent;
public:
    DUGraph(node_t V);
    size_t getV() const;
    void addEdge(node_t u, node_t v);
    const std::list<node_t>& Adj(node_t u) const;
};

#endif //DUGRAPH_H_INCLUDED
