#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "ShortestPathOneMany.h"

#include <vector>

class FloydWarshall : public ShortestPathOneMany {
private:
    const DWGraph *G;
    std::vector< std::vector<DWGraph::weight_t> > dist;
    std::vector< std::vector<long long> > next;
public:
    void initialize(const DWGraph *G);
    void run();

    DWGraph::weight_t pathWeight(const DWGraph *G, DWGraph::node_t u, DWGraph::node_t v);
    std::list<DWGraph::node_t> getPath();
};

#endif //FLOYDWARSHALL_H_INCLUDED