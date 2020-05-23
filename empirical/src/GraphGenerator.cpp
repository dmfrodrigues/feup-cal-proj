#include "GraphGenerator.h"

#include <iostream>

GraphGenerator::GraphGenerator(int numNodes_){
    this->G = new DWGraph::DWGraph();
    this->numNodes = numNodes_;
};

void GraphGenerator::run() {
    G->addNode(1);
    for (DWGraph::node_t u = 2; u <= numNodes; ++u) {
        G->addNode(u);
        DWGraph::node_t v = 1 + (rand() % (u - 1));
        G->addEdge(u, v, rand() % 10000 + 1);
        G->addEdge(v, u, rand() % 10000 + 1);
    }
}

int GraphGenerator::getNum() const {
    return numNodes;
}

DWGraph::DWGraph* GraphGenerator::getDWGraph() const {
    return G;
}