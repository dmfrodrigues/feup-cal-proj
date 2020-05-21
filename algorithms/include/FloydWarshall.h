#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "ShortestPathAll.h"
#include "DWGraph.h"

#include <vector>

class FloydWarshall: public ShortestPathAll {
private:
    const DWGraph::DWGraph *G;
    typedef size_t id_t;
    std::unordered_map<DWGraph::node_t, id_t> node2id;
    std::unordered_map<id_t, DWGraph::node_t> id2node;
    std::vector< std::vector<DWGraph::weight_t> > dist;
    std::vector< std::vector<DWGraph::node_t  > > prev;
    statistics_t stats;
public:
    FloydWarshall();
    void initialize(const DWGraph::DWGraph *G);
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t u, DWGraph::node_t v) const;
    statistics_t getStatistics() const;
};

#endif //FLOYDWARSHALL_H_INCLUDED