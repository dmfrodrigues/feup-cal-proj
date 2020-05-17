#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "ShortestPathOneMany.h"

#include <vector>

class FloydWarshall {
private:
    const DWGraph *G;
    std::vector< std::vector<DWGraph::weight_t> > dist;
    std::vector< std::vector<long long> > next;
public:
    void initialize();
    void run();

    DWGraph::weight_t pathWeight(DWGraph::node_t u, DWGraph::node_t v);
    std::list<DWGraph::node_t> getPath(DWGraph::node_t i, DWGraph::node_t j);
};

#endif //FLOYDWARSHALL_H_INCLUDED