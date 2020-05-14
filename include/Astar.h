#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include "ShortestPath.h"
#include <unordered_map>

class Astar : public ShortestPath {
public:
    typedef DWGraph::weight_t (*heuristic_t)(DWGraph::node_t);
private:
    heuristic_t h;
    const DWGraph *G;
    DWGraph::node_t s, d;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> dist;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> hdist;
    std::unordered_map<DWGraph::node_t, DWGraph::node_t  > prev;
public:
    Astar(heuristic_t h);
    void initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d);
    DWGraph::node_t getStart() const;
    DWGraph::node_t getDest () const;
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t u) const;
    DWGraph::weight_t getPathWeight() const;
};

#endif //ASTAR_H_INCLUDED
