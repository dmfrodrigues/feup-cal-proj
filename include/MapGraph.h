#ifndef MAPGRAPH_H_INCLUDED
#define MAPGRAPH_H_INCLUDED

#include "DWGraph.h"
#include "graphviewer.h"
#include "EdgeType.h"

class MapGraph {
public:
    typedef double speed_t;
private:
    struct pos_t {
        double lat, lon;
        /**
         * @brief Get distance between two positions in SI units (meters).
         * 
         * @param p1        First position
         * @param p2        Second position
         * @return double   Distance between them in meters
         */
        static double getDistanceSI(const pos_t &p1, const pos_t &p2);

        pos_t operator+(const pos_t &p) const;
        pos_t operator/(double d) const;
    private:
        double getMetersPerLatDeg() const;
        double getMetersPerLonDeg() const;
    };
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

    const DWGraph::node_t station = 1390706567;

    std::unordered_map<DWGraph::node_t, pos_t> nodes;
    std::list<way_t> ways;
    DWGraph G;
public:
    MapGraph(const std::string &path);
    DWGraph getFullGraph() const;
    DWGraph getConnectedGraph() const;
    void drawRoads (int fraction, int display) const;
    void drawSpeeds(int fraction, int display) const;
    void drawSCC   (int fraction, int display) const;
    class DistanceHeuristic;
    void drawPath  (int fraction, int display, DWGraph::node_t src, DWGraph::node_t dst, bool visited) const;
};

#endif //MAPGRAPH_H_INCLUDED
