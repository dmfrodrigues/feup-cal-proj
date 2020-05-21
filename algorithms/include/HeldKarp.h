#ifndef HELDKARP_H_INCLUDED
#define HELDKARP_H_INCLUDED

#include "TravellingSalesman.h"

#include <vector>

class HeldKarp : public TravellingSalesman {
public:
    typedef DWGraph::weight_t (*weight_function)(const std::unordered_set<DWGraph::node_t> &S, DWGraph::node_t u, DWGraph::node_t v);
private:
    typedef unsigned short id_t;
    static const id_t INVALID_ID;
    typedef unsigned long long set_t;
    template <class T> using state_struct = std::vector<std::vector<T> >;
    
    const weight_function w;
    const DWGraph::DWGraph *G;
    id_t s;
    std::list<DWGraph::node_t> path;
    statistics_t stats;
    std::unordered_map<DWGraph::node_t, id_t> node2id;
    std::unordered_map<id_t, DWGraph::node_t> id2node;
    state_struct<DWGraph::weight_t> D;
    state_struct<std::pair<set_t, id_t> > P;
    DWGraph::weight_t HK(const set_t &S, id_t v);

    DWGraph::weight_t w_wrapper(const set_t &S, id_t u, id_t v) const;
public:
    HeldKarp(weight_function w);
    void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s);
    void run();
    std::list<DWGraph::node_t> getTour() const;
    statistics_t getStatistics() const;
};

#endif //HELDKARP_H_INCLUDED
