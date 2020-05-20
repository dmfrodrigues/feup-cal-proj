#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include "ShortestPath.h"
#include <unordered_map>

class Astar : public ShortestPath {
public:
    class heuristic_t {
    public:
        virtual DWGraph::weight_t operator()(DWGraph::node_t u) const = 0;
    };
private:
    class default_heuristic : public heuristic_t {
    public:
        default_heuristic();
        DWGraph::weight_t operator()(DWGraph::node_t u) const;
    };
    static const default_heuristic h_default;
    const heuristic_t *h;
    const DWGraph::DWGraph *G;
    DWGraph::node_t s, d;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> dist;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> hdist;
    std::unordered_map<DWGraph::node_t, DWGraph::node_t  > prev;
    statistics_t stats;
public:
    Astar(const heuristic_t *h);
    Astar();
    void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s, DWGraph::node_t d);
    DWGraph::node_t getStart() const;
    DWGraph::node_t getDest () const;
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t u) const;
    DWGraph::weight_t getPathWeight() const;
    statistics_t getStatistics() const;
    bool hasVisited(DWGraph::node_t u) const;
};

#endif //ASTAR_H_INCLUDED
