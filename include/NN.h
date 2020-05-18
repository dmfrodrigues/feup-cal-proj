#ifndef NN_H_INCLUDED
#define NN_H_INCLUDED

#include "ShortestPath.h"

class NN : public ShortestPath {
private:
    const DWGraph *G;

public:
    void nearestNeighbour(DWGraph::node_t s);
    void initialize(const DWGraph *G);
    void run();

}

#endif //NN_H_INCLUDED