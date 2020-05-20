#include "NN.h"

#include <utility>

typedef DWGraph::node_t node_t;

void NN::initialize(const DWGraph *G) {
    this->G = G;
    for (int i = 0; i < G->getNodes().size(); i++) {
        // set NULL (for each vertex)
    }

    // clear Visited
}

void NN::nearestNeighbour(node_t s) {
    /*
    set Ans(0) = s;
    u' = s;
    for each int i = 1; i < nVertices
        add u' to the visited (and take from the non-visited?)
        find minimal dist u'
        Ans(i) = u';

    Ans(|V|) = s;  <-- back to the start point
    return Ans
    */
}