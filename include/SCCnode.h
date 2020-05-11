#ifndef SCC_NODE_H_INCLUDED
#define SCC_NODE_H_INCLUDED

#include "DUGraph.h"

class SCCnode{
public:
    virtual void initialize(const DUGraph *G, DUGraph::node_t s) = 0;
    virtual void run() = 0;
    virtual bool is_scc(DUGraph::node_t v) const = 0;
};

#endif //SCC_NODE_H_INCLUDED
