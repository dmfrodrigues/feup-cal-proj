#include "NN.h"

#include <utility>

typedef DWGraph::Edge Edge;
typedef DWGraph::weight_t weight_t;
typedef DWGraph::node_t node_t;
typedef std::chrono::high_resolution_clock hrc;

NN::NN() {}

void NN::initialize(const DWGraph::DWGraph *G_, DWGraph::node_t s_) {
    this->G = G_;
    this->s = s_;
    this->path.clear();
    this->visited.clear();

    this->path.push_back(this->s);
    this->visited.clear();
}

void NN::run() {
    auto start_time = hrc::now();

    node_t currentNode = this->s;

    for (size_t i = 0; i < G->getNodes().size() - 1; ++i) {

        // find u' (minimal dist from the set of non visited)
        node_t u_ = findClosest(currentNode);
        // printf("Iter: %d\tNode: %lld\n", i, u_);
        this->path.push_back(u_);
        this->visited.insert(u_);
        currentNode = u_;
    }
    // back to the starting node
    this->path.push_back(this->s);

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

node_t NN::findClosest(node_t u) {

    node_t minimizer = -1;
    weight_t weight = DWGraph::INF;

    for (const Edge &e: G->getAdj(u)) {
        // node cannot be the starting node (s) and must not have yet been visited
        if (e.v != this->s && (visited.find(e.v) == visited.end()) ) {
            // if (minimizer == NULL) {minimizer = e.v; weight = e.w;}
            if (e.w < weight) {
                minimizer = e.v;
                weight = e.w;
            }
        }
    }
    return minimizer;
}

std::list<DWGraph::node_t> NN::getTour() const {
    return this->path;
}

statistics_t NN::getStatistics() const {
    return stats;
}