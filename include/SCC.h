#ifndef SCC_H_INCLUDED
#define SCC_H_INCLUDED

#include "DUGraph.h"

class SCC{
public:
    virtual void initialize(const DUGraph *G) = 0;
    virtual void run() = 0;
    virtual DUGraph::node_t get_scc(DUGraph::node_t v) const = 0;
};

#endif //SCC_H_INCLUDED
