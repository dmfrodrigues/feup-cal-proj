#include "Astar.h"

#include <queue>

#include <iostream>

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

Astar::Astar(Astar::heuristic_t h){
    this->h = h;
}

void Astar::initialize(const DWGraph *G, node_t s, node_t d){
    this->G = G;
    this->s = s;
    this->d = d;
    dist.clear();
    hdist.clear();
    prev.clear();
    for(const node_t &u: G->getNodes()){
        dist[u] = DWGraph::INF;
        hdist[u] = DWGraph::INF;
        prev[u] = -1;
    }
}

node_t Astar::getStart() const { return s; }

node_t Astar::getDest () const { return d; }

void Astar::run(){
    min_priority_queue Q;
    dist[s] = 0; hdist[s] = h(s); Q.push(mk(hdist[s], s));
    while(!Q.empty()){
        node_t u = Q.top().second;
        Q.pop();
        if(u == d) break;
        for(const Edge &e: G->getAdj(u)){
            weight_t c_ = dist[u] + e.w;
            if(c_ < dist[e.v]){
                dist[e.v] = c_;
                hdist[e.v] = c_ + h(e.v);
                prev[e.v] = u;
                Q.push(mk(hdist[e.v], e.v));
            }
        }
    }
}

node_t Astar::getPrev(node_t u) const{
    return prev.at(u);
}

weight_t Astar::getPathWeight() const{
    return dist.at(d);
}
