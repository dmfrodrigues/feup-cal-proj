#include "Dijkstra.h"

#include <queue>
#include <utility>
#include <chrono>

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef DWGraph::Edge Edge;
template<class K, class V> using umap = std::unordered_map<K, V>;
typedef umap<node_t, weight_t> dist_t;
typedef umap<node_t, node_t  > prev_t;
typedef std::priority_queue<std::pair<weight_t, node_t>,
                std::vector<std::pair<weight_t, node_t>>,
               std::greater<std::pair<weight_t, node_t>>> min_priority_queue;
typedef std::chrono::high_resolution_clock hrc;
#define mk(a, b) (std::make_pair((a), (b)))

node_t Dijkstra::getStart() const{
    return s;
}

void Dijkstra::initialize(const DWGraph *G, DWGraph::node_t s){
    this->s = s;
    this->G = G;
    for(const node_t &u: G->getNodes()){
        dist[u] = DWGraph::INF;
        prev[u] = -1;
    }
}

void Dijkstra::run(){
    auto start_time = hrc::now();

    min_priority_queue Q;
    dist[s] = 0; Q.push(mk(dist[s], s)); ++stats.analysed_nodes;
    while(!Q.empty()){
        node_t u = Q.top().second; ++stats.analysed_nodes;
        Q.pop();
        for(const Edge &e: G->getAdj(u)){ ++stats.analysed_edges;
            weight_t c_ = dist[u] + e.w;
            if(c_ < dist[e.v]){
                dist[e.v] = c_;
                prev[e.v] = u;
                Q.push(mk(dist[e.v], e.v));
            }
        }
    }

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

DWGraph::node_t Dijkstra::getPrev(DWGraph::node_t d) const{
    return prev.at(d);
}

weight_t Dijkstra::getPathWeight(node_t d) const{
    return dist.at(d);
}

statistics_t Dijkstra::getStatistics() const {
    return stats;
}

bool Dijkstra::hasVisited(DWGraph::node_t u) const{
    return (dist.at(u) != DWGraph::INF);
}
