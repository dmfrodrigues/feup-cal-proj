#ifndef SHORTESTPATHONEMANY_H_INCLUDED
#define SHORTESTPATHONEMANY_H_INCLUDED

#include <list>

#include "DWGraph.h"

class ShortestPathOneMany {
public:
    virtual void initialize(const DWGraph *G, DWGraph::node_t s) = 0;
    virtual void run() = 0;
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t d) const = 0;
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t d) const = 0;
};

#endif //SHORTESTPATHONEMANY_H_INCLUDED
