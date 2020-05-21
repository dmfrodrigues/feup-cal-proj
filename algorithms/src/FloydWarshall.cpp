#include "FloydWarshall.h"

typedef DWGraph::weight_t weight_t;
typedef DWGraph::node_t node_t;
typedef DWGraph::Edge Edge;
typedef std::chrono::high_resolution_clock hrc;

FloydWarshall::FloydWarshall() {}

void FloydWarshall::initialize(const DWGraph::DWGraph *G_) {
    this->G = G_;
    
    const auto &V = G->getNodes();

    id_t id = 0;
    for(const node_t &u: V){
        node2id[u] = id;
        id2node[id] = u;
        ++id;
    }

    dist = std::vector< std::vector<DWGraph::weight_t> >(V.size(),std::vector<DWGraph::weight_t>(V.size(), DWGraph::INF));
    prev = std::vector< std::vector<DWGraph::node_t  > >(V.size(),std::vector<DWGraph::node_t  >(V.size()));
    
}

void FloydWarshall::run() {
    auto start_time = hrc::now();

    const auto &V = G->getNodes();

    for(const node_t &u: V){
        id_t u_id = node2id[u];
        dist[u_id][u_id] = 0;
        prev[u_id][u_id] = u_id;
        for(const Edge &e: G->getAdj(u)){
            id_t v_id = node2id[e.v];
            if(e.w < dist[u_id][v_id]){
                dist[u_id][v_id] = e.w;
                prev[u_id][v_id] = u_id;
            }
        }
    }

    for (size_t k = 0; k < V.size(); ++k) {
        for (size_t i = 0; i <  V.size(); ++i) {
            for (size_t j = 0; j < V.size(); ++j) {
                weight_t c_ = dist[i][k] + dist[k][j];
                if (c_ < dist[i][j]) {
                    dist[i][j] = c_;
                    prev[i][j] = prev[k][j];
                }
            }
        }
    }

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

DWGraph::node_t FloydWarshall::getPrev(DWGraph::node_t s, DWGraph::node_t d) const{
    return id2node.at(prev[node2id.at(s)][node2id.at(d)]);
}

weight_t FloydWarshall::getPathWeight(DWGraph::node_t u, DWGraph::node_t v) const{
    return dist[node2id.at(u)][node2id.at(v)];
}

statistics_t FloydWarshall::getStatistics() const {
    return stats;
}
