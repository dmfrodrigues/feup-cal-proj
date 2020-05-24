#ifndef NN_H_INCLUDED
#define NN_H_INCLUDED


#include "TravellingSalesman.h"

#include <unordered_set>

class NearestNeighbour : public TravellingSalesman {
private:
    const std::list<DWGraph::node_t> *nodes = nullptr;
    DWGraph::node_t s;
    weight_function *w = nullptr;
    std::list<DWGraph::node_t> path;
    std::unordered_multiset<DWGraph::node_t> visited, unvisited;
    statistics_t stats;
    
    DWGraph::node_t findClosest(DWGraph::node_t u);
public:
    NearestNeighbour();
    void initialize(const std::list<DWGraph::node_t> *nodes, DWGraph::node_t s, weight_function *w);
    void run();
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //NN_H_INCLUDED