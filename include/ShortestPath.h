#ifndef SHORTESTPATH_H_INCLUDED
#define SHORTESTPATH_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "ShortestPathOneMany.h"

class ShortestPath {
public:
    virtual ~ShortestPath();
    virtual void initialize(const DWGraph *G, DWGraph::node_t s, DWGraph::node_t d) = 0;
    virtual DWGraph::node_t getStart() const = 0;
    virtual DWGraph::node_t getDest () const = 0;
    virtual void run() = 0;
    virtual DWGraph::node_t getPrev(DWGraph::node_t u) const = 0;
    std::list<DWGraph::node_t> getPath() const;
    virtual DWGraph::weight_t getPathWeight() const = 0;
    class FromOneMany;
    struct statistics_t {
        size_t analysed_nodes;
        size_t analysed_edges;
    };
    virtual statistics_t getStatistics() const = 0;
    virtual bool hasVisited(DWGraph::node_t u) const = 0;
};

class ShortestPath::FromOneMany : public ShortestPath{
private:
    ShortestPathOneMany *oneMany = nullptr;
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
    virtual statistics_t getStatistics() const;
    virtual bool hasVisited(DWGraph::node_t u) const;
};

#endif //SHORTESTPATH_H_INCLUDED
