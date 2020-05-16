#ifndef FLOYDWARSHALL_H_INCLUDED
#define FLOYDWARSHALL_H_INCLUDED

#include "ShortestPathOneMany.h"

class FloydWarshall : public ShortestPathOneMany {
private:
    const DWGraph *G;
    DWGraph::node_t s;
    std::unordered_map<DWGraph::node_t, DWGraph::weight_t> dist;
    std::unordered_map<DWGraph::node_t, DWGraph::node_t> prev;
public:
    void initialize(const DWGraph *G, DWGraph::node_t s);
    void run();

    
}

#endif //FLOYDWARSHALL_H_INCLUDED