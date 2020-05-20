#ifndef DUGRAPH_H_INCLUDED
#define DUGRAPH_H_INCLUDED

#include <cstddef>
#include <unordered_map>
#include <list>

class DUGraph {
public:
    typedef size_t node_t;
private:
    std::list<node_t> nodes;
    std::unordered_map< node_t, std::list<node_t> > adj;
public:
    DUGraph();
    void addNode(node_t u);
    void addEdge(node_t u, node_t v);
    const std::list<node_t>& getNodes() const;
    const std::list<node_t>& getAdj(node_t u) const;
    DUGraph getTranspose() const;
};

#endif //DUGRAPH_H_INCLUDED
