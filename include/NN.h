#ifndef NN_H_INCLUDED
#define NN_H_INCLUDED

#include "DWGraph.h"

#include <unordered_set>

class NN {
private:
    const DWGraph::DWGraph *G;
    DWGraph::node_t s;
    std::list<DWGraph::node_t> path;
    std::unordered_set<node_t> visited;

public:
    NN();
    void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s);
    void run();
    node_t findClosest(node_t u);

};

#endif //NN_H_INCLUDED