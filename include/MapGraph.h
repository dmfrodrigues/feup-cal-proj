#ifndef MAPGRAPH_H_INCLUDED
#define MAPGRAPH_H_INCLUDED

#include "DWGraph.h"
#include "graphviewer.h"
#include "EdgeType.h"

class MapGraph {
public:
    typedef long long speed_t;
    struct pos_t {
        double lat, lon;
    };
    struct way_t {
        std::list<DWGraph::node_t> nodes;
        speed_t speed;
        edge_type_t edgeType;  
    };
private:
    std::unordered_map<DWGraph::node_t, pos_t> nodes;
    std::list<way_t> ways;
    DWGraph G;
public:
    MapGraph(const std::string &path);
    void draw(GraphViewer *gv) const;
};

#endif //MAPGRAPH_H_INCLUDED
