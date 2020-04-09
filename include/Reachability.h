#ifndef REACHABILITY_H_INCLUDED
#define REACHABILITY_H_INCLUDED

#include "DUGraph.h"

class Reachability{
public:
    virtual void initialize(const DUGraph *G, DUGraph::node_t s) = 0;
    virtual void run() = 0;
    virtual bool is_reachable(DUGraph::node_t v) const = 0;
};

#endif //REACHABILITY_H_INCLUDED
