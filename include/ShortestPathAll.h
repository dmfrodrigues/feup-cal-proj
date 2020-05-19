#ifndef SHORTESTPATHALL_H_INCLUDED
#define SHORTESTPATHALL_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"

class ShortestPathAll {
public:
    virtual void initialize(const DWGraph::DWGraph *G) = 0;
    virtual void run() = 0;
    virtual DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const = 0;
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const;
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const = 0;
    class FromOneMany;
};

class ShortestPathAll::FromOneMany : public ShortestPathAll {
private:
    ShortestPathOneMany *oneMany = nullptr;
    const DWGraph::DWGraph *G = nullptr;
    std::unordered_map<DWGraph::node_t, std::unordered_map<DWGraph::node_t, DWGraph::weight_t> > dist;
    std::unordered_map<DWGraph::node_t, std::unordered_map<DWGraph::node_t, DWGraph::node_t  > > prev;
public:
    FromOneMany(ShortestPathOneMany *oneMany);
    void initialize(const DWGraph::DWGraph *G);
    void run();
    DWGraph::node_t getPrev(DWGraph::node_t s, DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const;
};

#endif //SHORTESTPATHALL_H_INCLUDED
