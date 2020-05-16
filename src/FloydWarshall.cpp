#include "FloydWarshall.h"

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef DWGraph::Edge Edge;


void FloydWarshall::initialize(const DWGraph *G, DWGraph::node_t s) {
    this->s = s;
    this->G = G;

    for (const node_t &u : G->getNodes()) {
        dist[0][i][j] = DWGraph::INF;

        for (size_t k = 0; k < G->getNodes().size(); k++) {
            prev[k][i][j] = NULL;
        }
    }

    for (size_t i = 0; i < G->getNodes().size(); i++) {
        dist[0][i][i] = 0;
    }
}

void FloydWarshall::run() {
    
}