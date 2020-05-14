#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED

#include <list>

#include "DWGraph.h"

class ShortestPath {
public:
    virtual void initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d) = 0;
    virtual void run() = 0;
    virtual std::list<DWGraph::node_t> getPath() const = 0;
    virtual DWGraph::weight_t getPathWeight() const = 0;
};

#endif //SHORTESTPATH_H_INCLUDED
