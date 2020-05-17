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
    statistics_t stats;
    DWGraph::node_t getStart() const;
public:
    void initialize(const DWGraph *G, DWGraph::node_t s);
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t d) const;
    statistics_t getStatistics() const;
    bool hasVisited(DWGraph::node_t u) const;
};

#endif //DIJKSTRA_H_INCLUDED
