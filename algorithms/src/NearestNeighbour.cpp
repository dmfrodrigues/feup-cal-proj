#include "NearestNeighbour.h"

#include <utility>

typedef DWGraph::Edge Edge;
typedef DWGraph::weight_t weight_t;
typedef DWGraph::node_t node_t;
typedef std::chrono::high_resolution_clock hrc;

NearestNeighbour::NearestNeighbour() {}

void NearestNeighbour::initialize(const std::list<DWGraph::node_t> *nodes_, DWGraph::node_t s_, weight_function *w_) {
    this->nodes = nodes_;
    this->s = s_;
    this->w = w_;
    this->path.clear();
    this->visited.clear();

    this->path.push_back(this->s);
    this->visited.clear();
}

void NearestNeighbour::run() {
    auto start_time = hrc::now();

    node_t currentNode = this->s;

    for (size_t i = 0; i < nodes->size() - 1; ++i) {
        node_t u = findClosest(currentNode);
        this->path.push_back(u);
        this->visited.insert(u);
        currentNode = u;
    }
    // back to the starting node
    this->path.push_back(this->s);

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

node_t NearestNeighbour::findClosest(node_t u) {

    node_t ret = DWGraph::INVALID_NODE;
    weight_t c = DWGraph::INF;

    for (const node_t &v: *nodes) { if(v == u || v == s) continue;       // node cannot be the starting node (s)
        if (!visited.count(v)) {                                        // and must not have yet been visited
            weight_t c_ = w->operator()(visited, u, v);
            if (c_ < c) {
                c = c_;
                ret = v;
            }
        }
    }
    return ret;
}

std::list<DWGraph::node_t> NearestNeighbour::getTour() const {
    return path;
}

statistics_t NearestNeighbour::getStatistics() const {
    return stats;
}