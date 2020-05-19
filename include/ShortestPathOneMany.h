#ifndef SHORTESTPATHONEMANY_H_INCLUDED
#define SHORTESTPATHONEMANY_H_INCLUDED

#include <list>

#include "DWGraph.h"
#include "statistics.h"

class ShortestPathOneMany {
private:
    virtual DWGraph::node_t getStart() const = 0;
public:
    virtual ~ShortestPathOneMany();
    virtual void initialize(const DWGraph::DWGraph *G, DWGraph::node_t s) = 0;
    virtual void run() = 0;
    virtual DWGraph::node_t getPrev(DWGraph::node_t d) const = 0;
    virtual std::list<DWGraph::node_t> getPath(DWGraph::node_t d) const final;
    virtual DWGraph::weight_t getPathWeight(DWGraph::node_t d) const = 0;
    virtual statistics_t getStatistics() const = 0;
    virtual bool hasVisited(DWGraph::node_t u) const = 0;
};

#endif //SHORTESTPATHONEMANY_H_INCLUDED
