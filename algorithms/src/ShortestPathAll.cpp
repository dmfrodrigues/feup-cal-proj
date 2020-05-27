#include "ShortestPathAll.h"

#include <chrono>

#include <iostream>

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef std::chrono::high_resolution_clock hrc;

ShortestPathAll::~ShortestPathAll(){}

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
    this->oneMany  = oneMany_ ;
    this->nthreads = nthreads_;
}

void ShortestPathAll::FromOneMany::initialize(const DWGraph::DWGraph *G_, const std::unordered_set<node_t> &V){
    this->G = G_;
    nodes = std::list<node_t>(V.begin(), V.end());
    
    for(const node_t &u: V){
        Q.push(u);
        for(const node_t &v: V){
            dist[u][v] = DWGraph::INF;
        }
        dist[u][u] = 0;
    }
}

void ShortestPathAll::FromOneMany::initialize(const DWGraph::DWGraph *G_){
    initialize(G_, G_->getNodes());
}

void ShortestPathAll::FromOneMany::thread_func(ShortestPathAll::FromOneMany *p){
    node_t s;
    ShortestPathOneMany *sp = p->oneMany->clone();
    while(true){
        try{
            s = p->Q.pop();
        } catch(const std::logic_error &e) {
            break;
        }
        auto &dist = p->dist.at(s);
        sp->initialize(p->G, s);
        sp->run();
        for(const node_t &v: p->nodes){
            if(v == s) continue;
            dist.at(v) = sp->getPathWeight(v);
        }
    }
    delete sp;
}

void ShortestPathAll::FromOneMany::run(){
    auto start_time = hrc::now();
    for(size_t i = 0; i < nthreads-1; ++i) threads.push_back(std::thread(thread_func, this));
    thread_func(this);
    for(size_t i = 0; i < nthreads-1; ++i) threads[i].join();
    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

node_t ShortestPathAll::FromOneMany::getPrev(node_t, node_t) const{
    return DWGraph::INVALID_NODE;
}

weight_t ShortestPathAll::FromOneMany::getPathWeight(node_t s, node_t d) const{
    return dist.at(s).at(d);
}

statistics_t ShortestPathAll::FromOneMany::getStatistics() const {
    return stats;
}
