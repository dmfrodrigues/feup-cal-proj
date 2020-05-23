#ifndef TRAVELLINGSALESMAN_H_INCLUDED
#define TRAVELLINGSALESMAN_H_INCLUDED

#include "DWGraph.h"
#include "statistics.h"
#include <chrono>

class TravellingSalesman{
public:
    class weight_function{
    public:
        virtual ~weight_function();
        virtual DWGraph::weight_t operator()(const std::unordered_set<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const = 0;
    };

    virtual ~TravellingSalesman();

    virtual void initialize(const std::list<DWGraph::node_t> *nodes, DWGraph::node_t s, weight_function *w) = 0;
    virtual void run() = 0;
    virtual std::list<DWGraph::node_t> getTour() const = 0;
    virtual statistics_t getStatistics() const = 0;
};

#endif //TRAVELLINGSALESMAN_H_INCLUDED