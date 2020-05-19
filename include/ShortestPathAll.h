#ifndef SHORTESTPATHALL_H_INCLUDED
#define SHORTESTPATHALL_H_INCLUDED

#include <list>
#include <vector>
#include <queue>
#include <thread>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"

class ShortestPathAll {
public:
    virtual void initialize(const DWGraph::DWGraph *G) = 0;
    virtual void run() = 0;
    virtual DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const = 0;
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const final;
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const = 0;
    virtual statistics_t getStatistics() const = 0;
    class FromOneMany;
};

class ShortestPathAll::FromOneMany : public ShortestPathAll {
private:
    typedef uint16_t id_t;
    static const id_t INVALID_ID;
    size_t nthreads;
    std::vector< std::queue<DWGraph::node_t> > threads_nodes;
    std::vector< std::thread > threads;
    std::vector<ShortestPathOneMany*> oneManys;
    const DWGraph::DWGraph *G = nullptr;
    std::unordered_map<DWGraph::node_t, id_t> node2id;
    std::unordered_map<id_t, DWGraph::node_t> id2node;
    std::vector< std::vector<id_t> > prev;
    statistics_t stats;
    static void thread_func(ShortestPathAll::FromOneMany *p, size_t i);
public:
    FromOneMany(ShortestPathOneMany *oneMany, size_t nthreads);
    void initialize(const DWGraph::DWGraph *G);
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const;
    statistics_t getStatistics() const;
};

#endif //SHORTESTPATHALL_H_INCLUDED
