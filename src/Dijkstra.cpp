#include "Dijkstra.h"

#include <queue>
#include <utility>

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef DWGraph::Edge Edge;
template<class K, class V> using umap = std::unordered_map<K, V>;
typedef umap<node_t, weight_t> dist_t;
typedef umap<node_t, node_t  > prev_t;
typedef std::priority_queue<std::pair<weight_t, node_t>,
                std::vector<std::pair<weight_t, node_t>>,
               std::greater<std::pair<weight_t, node_t>>> min_priority_queue;
#define mk(a, b) (std::make_pair((a), (b)))

void Dijkstra::initialize(const DWGraph *G){
    this->G = G;
    for(const node_t &u: G->getNodes()){
        for(const node_t &v: G->getNodes()){
            dist_[u][v] = DWGraph::INF;
            prev_[u][v] = -1;            
        }
    }
}

void Dijkstra::dijkstra(node_t s){
    dist_t &dist = dist_[s];
    prev_t &prev = prev_[s];
    min_priority_queue Q;
    dist[s] = 0; Q.push(mk(dist[s], s));
    while(!Q.empty()){
        node_t u = Q.top().second;
        Q.pop();
        for(const Edge &e: G->getAdj(u)){
            weight_t c_ = dist[u] + e.w;
            if(c_ < dist[e.v]){
                dist[e.v] = c_;
                prev[e.v] = u;
                Q.push(mk(dist[e.v], e.v));
            }
        }
    }

}

void Dijkstra::run(){
    for(const node_t &s: G->getNodes()){
        dijkstra(s);
    }
}

std::list<node_t> Dijkstra::getPath(node_t s, node_t d) const{
    return std::list<node_t>();
}

weight_t Dijkstra::getPathWeight(node_t s, node_t d) const{
    return dist_.at(s).at(d);
}
