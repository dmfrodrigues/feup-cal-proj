#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include "ShortestPath.h"

#include <unordered_map>

class Dijkstra : public ShortestPath {
private:
    const DWGraph *G;
    std::unordered_map<DWGraph::node_t, std::unordered_map<DWGraph::node_t, DWGraph::weight_t> > dist_;
    // If I am in `i` and want to go to `j`, to get closer to `j` I need to go to `prev_[j][i]`.
    std::unordered_map<DWGraph::node_t, std::unordered_map<DWGraph::node_t, DWGraph::node_t> > prev_;

    void dijkstra(DWGraph::node_t s);
public:
    void initialize(const DWGraph *G);
    void run();
    std::list<DWGraph::node_t> getPath(DWGraph::node_t s, DWGraph::node_t d) const;
    DWGraph::weight_t getPathWeight(DWGraph::node_t s, DWGraph::node_t d) const;
};

#endif //DFS_H_INCLUDED
