#include "HeldKarp.h"

#define POW2(n) (1uL << n)
#define SET_EMPTY 0uL
#define SET_FULL(n) (POW2(n)-1)
#define SET_INSERT(V, u) (V |= POW2(u))
#define SET_CONTAINS(V, u) (V & POW2(u))
#define SET_WITHOUT(V, u) (V & (~POW2(u)))

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;
typedef std::chrono::high_resolution_clock hrc;

const HeldKarp::id_t HeldKarp::INVALID_ID = std::numeric_limits<HeldKarp::id_t>::max();

HeldKarp::HeldKarp(){}

void HeldKarp::initialize(const std::list<DWGraph::node_t> *nodes_, DWGraph::node_t s_, weight_function *w_){
    // Nodes
    id_t id = 0;
    for(const node_t &u: *nodes_){
        node2id[u] = id;
        id2node[id] = u;
        ++id;
    }
    // Source
    this->s = node2id.at(s_);
    // Weight function
    w = w_;
    // Others
    set_t S = SET_FULL(nodes_->size());
    D = state_struct<weight_t>(S+1, 
        std::vector<weight_t>(nodes_->size(), DWGraph::INF)
    );
    P = state_struct< std::pair<set_t, id_t> >(S+1,
        std::vector< std::pair<set_t, id_t> >(nodes_->size(), std::make_pair(0, INVALID_ID))
    );
}

weight_t HeldKarp::w_wrapper(const HeldKarp::set_t &S, HeldKarp::id_t u, HeldKarp::id_t v) const{
    std::unordered_set<node_t> S_;
    for(id_t i = 0; i < id2node.size(); ++i) if(SET_CONTAINS(S, i)) S_.insert(id2node.at(i));
    return w->operator()(S_, id2node.at(u), id2node.at(v));
}

weight_t HeldKarp::HK(const HeldKarp::set_t &S, id_t v){
    if(D[S][v] != DWGraph::INF) return D[S][v];
    if(!SET_CONTAINS(S, s)) return DWGraph::INF;
    if(v == s){
        set_t T = SET_EMPTY; SET_INSERT(T, s);
        if(S == T) return (D[S][v] = 0);
        else       return DWGraph::INF;
    }
    set_t Sv = SET_WITHOUT(S, v);
    for(id_t u = 0; u < id2node.size(); ++u){
        if(!SET_CONTAINS(Sv, u)) continue;
        weight_t c = HK(Sv, u) + w_wrapper(Sv, u, v);
        if(c < D[S][v]){
            P[S][v] = std::make_pair(Sv, u);
            D[S][v] = c;
        }
    }    
    return D[S][v];
}

void HeldKarp::run(){
    auto start_time = hrc::now();

    set_t V = SET_FULL(id2node.size());
    std::pair< set_t, id_t> cur(V, INVALID_ID);
    weight_t c = DWGraph::INF;
    for(id_t u = 0; u < id2node.size(); ++u){
        if(u == s) continue;
        weight_t c_ = HK(V, u) + w_wrapper(V, u, s);
        if(c_ < c){
            c = c_;
            cur.second = u;
        }
    }

    path.clear();
    path.push_front(id2node.at(s));
    do{
        path.push_front(id2node.at(cur.second));
        cur = P[cur.first][cur.second];
    }while(cur.second != s);
    path.push_front(id2node.at(s));

    auto finish_time = hrc::now();
    stats.execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
}

std::list<node_t> HeldKarp::getTour() const{
    return path;
}

statistics_t HeldKarp::getStatistics() const{
    return stats;
}
