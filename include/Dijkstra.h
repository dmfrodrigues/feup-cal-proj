#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "ShortestPathOneMany.h"

#include <unordered_map>

class Dijkstra : public ShortestPathOneMany {
private:
    const DWGraph *G;
    DWGraph::node_t s;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> dist;
    std::unordered_map<DWGraph::node_t, DWGraph::node_t> prev;
public:
    void initialize(const DWGraph *G, DWGraph::node_t s);
    void run();
    std::list<DWGraph::node_t> getPath(DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t d) const;
};

#endif //DIJKSTRA_H_INCLUDED
