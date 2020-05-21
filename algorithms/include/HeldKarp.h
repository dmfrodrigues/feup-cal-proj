#ifndef HELDKARP_H_INCLUDED
#define HELDKARP_H_INCLUDED

#include "TravellingSalesman.h"

class HeldKarp : public TravellingSalesman {
private:
    const DWGraph::DWGraph *G;
    DWGraph::node_t s;
    std::list<DWGraph::node_t> path;
    statistics_t stats;
public:
    HeldKarp();
    void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s);
    void run();
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //HELDKARP_H_INCLUDED
