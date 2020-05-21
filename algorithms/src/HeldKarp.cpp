#include "HeldKarp.h"

#define POW2(n) (1uL << n)
#define SET_EMPTY 0uL
#define SET_FULL(n) (POW2(n)-1)
#define SET_INSERT(V, u) (V |= POW2(u))
#define SET_CONTAINS(V, u) (V & POW2(u))
#define SET_WITHOUT(V, u) (V & (~POW2(u)))

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

const HeldKarp::id_t HeldKarp::INVALID_ID = std::numeric_limits<HeldKarp::id_t>::max();

HeldKarp::HeldKarp(HeldKarp::weight_function w_):w(w_){}

void HeldKarp::initialize(const DWGraph::DWGraph *G_, node_t s_){
    this->G = G_;
    const std::unordered_set<node_t> &V = G->getNodes();
    id_t id = 0;
    for(const node_t &u: V){
        node2id[u] = id;
        id2node[id] = u;
        ++id;
    }
    this->s = node2id.at(s_);
    set_t S = SET_FULL(V.size());
    D = state_struct<weight_t>(S+1, 
        std::vector<weight_t>(V.size(), DWGraph::INF)
    );
    P = state_struct< std::pair<set_t, id_t> >(S+1,
        std::vector< std::pair<set_t, id_t> >(V.size(), std::make_pair(0, INVALID_ID))
    );
}

weight_t HeldKarp::w_wrapper(const HeldKarp::set_t &S, HeldKarp::id_t u, HeldKarp::id_t v) const{
    std::unordered_set<node_t> S_;
    for(id_t i = 0; i < id2node.size(); ++i) if(SET_CONTAINS(S, i)) S_.insert(id2node.at(i));
    return w(S_, id2node.at(u), id2node.at(v));
}

weight_t HeldKarp::HK(const HeldKarp::set_t &S, id_t v){
    if(D[S][v] != DWGraph::INF) return D[S][v];
    set_t T = SET_EMPTY; SET_INSERT(T, v);
    if(S == T) return (D[S][v] = w_wrapper(SET_EMPTY, s, v));
    for(id_t u = 0; u < id2node.size(); ++u){ if(!SET_CONTAINS(SET_WITHOUT(S, v), u)) continue;
        weight_t c = HK(SET_WITHOUT(S, v), u) + w_wrapper(SET_WITHOUT(S, v), u, v);
        if(c < D[S][v]){
            P[S][v] = std::make_pair(SET_WITHOUT(S, v), u);
            D[S][v] = c;
        }
    }    
    return 0;
}

void HeldKarp::run(){
    set_t V = SET_FULL(id2node.size());
    HK(V, s);
    
    path.clear();
    std::pair< set_t, id_t> cur(V, s);
    while(cur.second != INVALID_ID){
        path.push_front(id2node.at(cur.second));
        cur = P[cur.first][cur.second];
    }
    path.push_front(id2node.at(s));
}

std::list<node_t> HeldKarp::getTour() const{
    return path;
}

statistics_t HeldKarp::getStatistics() const{
    return stats;
}
