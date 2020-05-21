#ifndef NN_H_INCLUDED
#define NN_H_INCLUDED


#include "TravellingSalesman.h"

#include <unordered_set>

class NearestNeighbour : public TravellingSalesman {
private:
    const DWGraph::DWGraph *G;
    DWGraph::node_t s;
    std::list<DWGraph::node_t> path;
    std::unordered_set<DWGraph::node_t> visited;
    statistics_t stats;
    
    DWGraph::node_t findClosest(DWGraph::node_t u);
public:
    NearestNeighbour();
    void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s);
    void run();
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //NN_H_INCLUDED