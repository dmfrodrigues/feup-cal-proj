#ifndef MAPGRAPH_H_INCLUDED
#define MAPGRAPH_H_INCLUDED

#include "DWGraph.h"
#include "graphviewer.h"
#include "EdgeType.h"

class MapGraph {
public:
    typedef int speed_t;
    struct pos_t {
        double lat, lon;
    };
    struct way_t {
        std::list<DWGraph::node_t> nodes;
        speed_t speed;
        edge_type_t edgeType;
        speed_t getMaxSpeed() const;
    };
    enum Display {
        MOTORWAY    = 1,
        TRUNK       = 2,
        PRIMARY     = 4,
        SECONDARY   = 8,
        TERTIARY    = 16,
        ROAD        = 32,
        RESIDENTIAL = 64,
        SLOW        = 128
    };
private:
    std::unordered_map<DWGraph::node_t, pos_t> nodes;
    std::list<way_t> ways;
    DWGraph G;
public:
    MapGraph(const std::string &path);
    void drawRoads (GraphViewer *gv, int fraction, int display) const;
    void drawSpeeds(GraphViewer *gv, int fraction, int display) const;
};

#endif //MAPGRAPH_H_INCLUDED
