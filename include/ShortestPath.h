#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED

#include <list>

#include "DWGraph.h"

class ShortestPath {
public:
    virtual void initialize(const DWGraph *G) = 0;
    virtual void run() = 0;
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const = 0;
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const = 0;
};

#endif //SHORTESTPATH_H_INCLUDED
