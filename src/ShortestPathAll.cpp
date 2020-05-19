#include "ShortestPathAll.h"

#include <chrono>

#include <iostream>

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef std::chrono::high_resolution_clock hrc;

const ShortestPathAll::FromOneMany::id_t ShortestPathAll::FromOneMany::INVALID_ID = std::numeric_limits<id_t>::max();

std::list<node_t> ShortestPathAll::getPath(node_t s, node_t d) const{
    std::list<node_t> res;
    while(d != s){
        res.push_front(d);
        d = getPrev(s, d);
        if(d == DWGraph::INVALID_NODE) return std::list<node_t>();
    }
    res.push_front(d);
    return res;
}

ShortestPathAll::FromOneMany::FromOneMany(ShortestPathOneMany *oneMany_, size_t nthreads_){
    this->oneMany = oneMany_;
    this->nthreads = nthreads_;
}

void ShortestPathAll::FromOneMany::initialize(const DWGraph::DWGraph *G_){
    this->G = G_;
    const auto &V = G->getNodes();
    // IDs
    id_t id = 0;
    for(const node_t &u: V){
        node2id[u] = id;
        id2node[id] = u;
        ++id;
    }
    node2id[DWGraph::INVALID_NODE] = INVALID_ID;
    id2node[INVALID_ID] = DWGraph::INVALID_NODE;
    // Prev
    prev = std::vector< std::vector<id_t> >(id, std::vector<id_t>(id));
    // Threads
    threads_nodes = std::vector< std::queue<node_t> >(nthreads);
    std::queue<node_t> Q; for(const node_t &u: V) Q.push(u);
    for(size_t i = 0; i < nthreads; ++i){
        const size_t N = Q.size()/(nthreads-i);
        for(size_t n = 0; n < N; ++n){
            threads_nodes[i].push(Q.front());
            Q.pop();
        }
    }
}

void ShortestPathAll::FromOneMany::thread_func(ShortestPathAll::FromOneMany *p, size_t i){
    auto &Q = p->threads_nodes[i];
    while(!Q.empty()){
        node_t s = Q.front(); Q.pop();
        p->oneMany->initialize(p->G, s);
        p->oneMany->run();
        for(const node_t &d: p->G->getNodes()){
            p->prev[p->node2id.at(s)][p->node2id.at(d)] = p->node2id.at(p->oneMany->getPrev(d));
        }
    }
}

void ShortestPathAll::FromOneMany::run(){
    auto start_time = hrc::now();

    for(size_t i = 0; i < nthreads; ++i){
        //threads.push_back(std::thread(thread_func, i));
        thread_func(this, i);
    }

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

node_t ShortestPathAll::FromOneMany::getPrev(node_t s, node_t d) const{
    return id2node.at(prev[node2id.at(s)][node2id.at(d)]);
}

weight_t ShortestPathAll::FromOneMany::getPathWeight(node_t s, node_t d) const{
    return G->getPathWeight(getPath(s, d));
}

statistics_t ShortestPathAll::FromOneMany::getStatistics() const {
    return stats;
}
