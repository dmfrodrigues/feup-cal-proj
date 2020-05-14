#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"

class ShortestPath {
public:
    virtual void initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d) = 0;
    virtual DWGraph::node_t getStart() const = 0;
    virtual DWGraph::node_t getDest () const = 0;
    virtual void run() = 0;
    virtual DWGraph::node_t getPrev(DWGraph::node_t u) const = 0;
    std::list<DWGraph::node_t> getPath() const;
    virtual DWGraph::weight_t getPathWeight() const = 0;
    class FromOneMany;
};

class ShortestPath::FromOneMany : public ShortestPath{
private:
    ShortestPathOneMany *oneMany = NULL;
    const DWGraph *G;
    DWGraph::node_t s, d;
public:
    FromOneMany(ShortestPathOneMany *oneMany);
    virtual void initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d);
    virtual void run();
    virtual DWGraph::node_t getStart() const;
    virtual DWGraph::node_t getDest () const;
    virtual DWGraph::node_t getPrev(DWGraph::node_t u) const;
    virtual DWGraph::weight_t getPathWeight() const;
};

#endif //SHORTESTPATH_H_INCLUDED
