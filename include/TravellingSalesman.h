#ifndef TRAVELLINGSALESMAN_H_INCLUDED
#define TRAVELLINGSALESMAN_H_INCLUDED

#include "DWGraph.h"

class TravellingSalesman{
public:
    virtual void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s) = 0;
    virtual void run() = 0;
    virtual std::list<DWGraph::node_t> getTour() const = 0;
};

#endif //TRAVELLINGSALESMAN_H_INCLUDED