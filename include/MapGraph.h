#ifndef MAPGRAPH_H_INCLUDED
#define MAPGRAPH_H_INCLUDED

#include "DWGraph.h"
#include "graphviewer.h"
#include "EdgeType.h"
#include "coord.h"

class MapGraph {
public:
    typedef double speed_t;
private:
    struct way_t {
        std::list<DWGraph::node_t> nodes;
        speed_t speed;
        edge_type_t edgeType;
        /**
         * @brief Get the maximum speed in km/h
         * 
         * @return speed_t 
         */
        speed_t getMaxSpeed() const;
        /**
         * @brief Get the real speed in m/s
         * 
         * @return speed_t 
         */
        speed_t getRealSpeed() const;
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
    static const std::unordered_map<edge_type_t, Display> display_map;

    static const DWGraph::node_t station = 1390706567;

    std::unordered_map<DWGraph::node_t, coord_t> nodes;
    coord_t min_coord, max_coord, mean_coord;
    std::list<way_t> ways;
public:
    MapGraph(const std::string &path);
    DWGraph::DWGraph getFullGraph() const;
    DWGraph::DWGraph getConnectedGraph() const;
    DWGraph::DWGraph getReducedGraph() const;
    void drawRoads (int fraction, int display) const;
    void drawSpeeds(int fraction, int display) const;
    void drawSCC   (int fraction, int display) const;
    class DistanceHeuristic;
    void drawPath  (int fraction, int display, DWGraph::node_t src, DWGraph::node_t dst, bool visited) const;
    void drawPath  (int fraction, int display, coord_t src, coord_t dst, bool visited) const;
    void drawReduced() const;
};

#endif //MAPGRAPH_H_INCLUDED
