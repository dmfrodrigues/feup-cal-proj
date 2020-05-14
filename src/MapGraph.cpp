#include "MapGraph.h"

#include "Astar.h"
#include "KosarajuV.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "ShortestPath.h"

#include <fstream>
#include <unordered_set>
#include <map>
#include <vector>

#include <cmath>

#define COORDMULT               50000       // Multiply coordinates to get integer positions
#define SECONDS_TO_MICROS       1000000     // Convert seconds to milliseconds
#define KMH_TO_MS               (1/3.6)     // Convert km/h to m/s
#define SPEED_REDUCTION_FACTOR  0.75        // Reduce speed to account for intense road traffic, and the fact people not always travel at maximum speed 

typedef DWGraph::node_t node_t;

double MapGraph::pos_t::getDistanceSI(const MapGraph::pos_t &p1, const MapGraph::pos_t &p2){
    pos_t m = (p1+p2)/2;
    double dlat = p2.lat - p1.lat;
    double dlon = p2.lon - p1.lon;
    double dx = m.getMetersPerLatDeg() * dlat;
    double dy = m.getMetersPerLonDeg() * dlon;
    return sqrt(dx*dx + dy*dy);
}

MapGraph::pos_t MapGraph::pos_t::operator+(const MapGraph::pos_t &p) const{
    pos_t ret;
    ret.lat = lat + p.lat;
    ret.lon = lon + p.lon;
    return ret;
}

MapGraph::pos_t MapGraph::pos_t::operator/(double d) const{
    pos_t ret = *this;
    ret.lat /= d;
    ret.lon /= d;
    return ret;
}

double MapGraph::pos_t::getMetersPerLatDeg() const{
    double phi = lat*M_PI/180;
    return 111132.92
          -   559.82  *cos(2*phi)
          +     1.175 *cos(4*phi)
          -     0.0023*cos(6*phi);
}
double MapGraph::pos_t::getMetersPerLonDeg() const{
    double phi = lat*M_PI/180;
    return 111412.84 *cos(  phi)
          -    93.5  *cos(3*phi)
          +     0.118*cos(5*phi);
}

MapGraph::speed_t MapGraph::way_t::getMaxSpeed() const{
    if(speed != -1) return speed;
    switch(edgeType){
        case edge_type_t::MOTORWAY       : return 120;
        case edge_type_t::MOTORWAY_LINK  : return  60;
        case edge_type_t::TRUNK          : return 100;
        case edge_type_t::TRUNK_LINK     : return  50;
        case edge_type_t::PRIMARY        : return  90;
        case edge_type_t::PRIMARY_LINK   : return  40;
        case edge_type_t::SECONDARY      : return  70;
        case edge_type_t::SECONDARY_LINK : return  30;
        case edge_type_t::TERTIARY       : return  50;
        case edge_type_t::TERTIARY_LINK  : return  30;
        case edge_type_t::UNCLASSIFIED   : return  30;
        case edge_type_t::RESIDENTIAL    : return  30;
        case edge_type_t::LIVING_STREET  : return  10;
        case edge_type_t::SERVICE        : return  20;
        default: throw invalid_argument("");
    }
}

MapGraph::speed_t MapGraph::way_t::getRealSpeed() const{
    if(speed != -1) return speed;
    switch(edgeType){
        case edge_type_t::MOTORWAY       : return 120*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::MOTORWAY_LINK  : return  60*KMH_TO_MS;
        case edge_type_t::TRUNK          : return 100*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::TRUNK_LINK     : return  50*KMH_TO_MS;
        case edge_type_t::PRIMARY        : return  90*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::PRIMARY_LINK   : return  40*KMH_TO_MS;
        case edge_type_t::SECONDARY      : return  70*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::SECONDARY_LINK : return  30*KMH_TO_MS;
        case edge_type_t::TERTIARY       : return  50*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::TERTIARY_LINK  : return  30*KMH_TO_MS;
        case edge_type_t::UNCLASSIFIED   : return  30*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::RESIDENTIAL    : return  30*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::LIVING_STREET  : return  10*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        case edge_type_t::SERVICE        : return  20*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
        default: throw invalid_argument("");
    }
}

MapGraph::MapGraph(const std::string &path){
    {
        ifstream is(path + ".nodes");
        size_t numberNodes; is >> numberNodes;
        for(size_t i = 0; i < numberNodes; ++i){
            node_t id; pos_t p; is >> id >> p.lat >> p.lon;
            nodes[id] = p;
        }
    }
    {
        ifstream is(path + ".edges");
        size_t numberWays; is >> numberWays; 
        for(size_t i = 0; i < numberWays; ++i){
            way_t way; char c;
            is >> c >> way.speed; way.edgeType = static_cast<edge_type_t>(c);
            size_t numberNodes; is >> numberNodes;
            for(size_t j = 0; j < numberNodes; ++j){
                node_t id; is >> id;
                way.nodes.push_back(id);
            }
            ways.push_back(way);
        }
    }
}

DWGraph MapGraph::getFullGraph() const{
    DWGraph G;
    for(const auto &p: nodes) G.addNode(p.first);
    for(const way_t &w: ways){
        if(w.nodes.size() < 2) continue;
        auto it1 = w.nodes.begin();
        for(auto it2 = it1++; it1 != w.nodes.end(); ++it1, ++it2){
            auto d = pos_t::getDistanceSI(nodes.at(*it1), nodes.at(*it2));
            DWGraph::weight_t t_ms = SECONDS_TO_MICROS * d / w.getRealSpeed();
            G.addEdge(*it2, *it1, t_ms);
        }
    }
    return G;
}

const std::unordered_map<edge_type_t, MapGraph::Display> MapGraph::display_map = {
    {edge_type_t::MOTORWAY      , Display::MOTORWAY   },
    {edge_type_t::MOTORWAY_LINK , Display::MOTORWAY   },
    {edge_type_t::TRUNK         , Display::TRUNK      },
    {edge_type_t::TRUNK_LINK    , Display::TRUNK      },
    {edge_type_t::PRIMARY       , Display::PRIMARY    },
    {edge_type_t::PRIMARY_LINK  , Display::PRIMARY    },
    {edge_type_t::SECONDARY     , Display::SECONDARY  },
    {edge_type_t::SECONDARY_LINK, Display::SECONDARY  },
    {edge_type_t::TERTIARY      , Display::TERTIARY   },
    {edge_type_t::TERTIARY_LINK , Display::TERTIARY   },
    {edge_type_t::UNCLASSIFIED  , Display::ROAD       },
    {edge_type_t::RESIDENTIAL   , Display::RESIDENTIAL},
    {edge_type_t::LIVING_STREET , Display::SLOW       },
    {edge_type_t::SERVICE       , Display::SLOW       }
};

GraphViewer* createGraphViewer(int w = 1800, int h = 900){
    GraphViewer *gv = new GraphViewer(w, h, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(w, h);
    return gv;
}

void MapGraph::drawRoads(int fraction, int display) const{
    GraphViewer *gv = createGraphViewer();
    
    static const std::unordered_map<edge_type_t, bool> dashed_map = {
        {edge_type_t::MOTORWAY      , false},
        {edge_type_t::MOTORWAY_LINK , false},
        {edge_type_t::TRUNK         , false},
        {edge_type_t::TRUNK_LINK    , false},
        {edge_type_t::PRIMARY       , false},
        {edge_type_t::PRIMARY_LINK  , false},
        {edge_type_t::SECONDARY     , false},
        {edge_type_t::SECONDARY_LINK, false},
        {edge_type_t::TERTIARY      , false},
        {edge_type_t::TERTIARY_LINK , false},
        {edge_type_t::UNCLASSIFIED  , false},
        {edge_type_t::RESIDENTIAL   , false},
        {edge_type_t::LIVING_STREET , true },
        {edge_type_t::SERVICE       , true }
    };
    static const std::unordered_map<edge_type_t, int> width_map = {
        {edge_type_t::MOTORWAY      , 10},
        {edge_type_t::MOTORWAY_LINK , 10},
        {edge_type_t::TRUNK         , 10},
        {edge_type_t::TRUNK_LINK    , 10},
        {edge_type_t::PRIMARY       ,  7},
        {edge_type_t::PRIMARY_LINK  ,  7},
        {edge_type_t::SECONDARY     ,  7},
        {edge_type_t::SECONDARY_LINK,  7},
        {edge_type_t::TERTIARY      ,  5},
        {edge_type_t::TERTIARY_LINK ,  5},
        {edge_type_t::UNCLASSIFIED  ,  5},
        {edge_type_t::RESIDENTIAL   ,  5},
        {edge_type_t::LIVING_STREET ,  5},
        {edge_type_t::SERVICE       ,  5}
    };
    static const std::unordered_map<edge_type_t, string> color_map = {
        {edge_type_t::MOTORWAY      , "RED"    },
        {edge_type_t::MOTORWAY_LINK , "RED"    },
        {edge_type_t::TRUNK         , "PINK"   },
        {edge_type_t::TRUNK_LINK    , "PINK"   },
        {edge_type_t::PRIMARY       , "ORANGE" },
        {edge_type_t::PRIMARY_LINK  , "ORANGE" },
        {edge_type_t::SECONDARY     , "YELLOW" },
        {edge_type_t::SECONDARY_LINK, "YELLOW" },
        {edge_type_t::TERTIARY      , "GRAY"   },
        {edge_type_t::TERTIARY_LINK , "GRAY"   },
        {edge_type_t::UNCLASSIFIED  , "GRAY"   },
        {edge_type_t::RESIDENTIAL   , "GRAY"   },
        {edge_type_t::LIVING_STREET , "GRAY"   },
        {edge_type_t::SERVICE       , "GRAY"   }
    };
    

    double lat_max = -90;
    double lon_min = +180;
    for(const auto &u: nodes){
        lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon);
    }
    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        string color = color_map.at(way.edgeType);
        int width = width_map.at(way.edgeType);
        bool dashed = dashed_map.at(way.edgeType);
        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
                    gv->addNode(v, x, y);
                    drawn_nodes.insert(v);
                }
                if(u != 0){
                    gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
                    gv->setEdgeColor(edge_id, color);
                    gv->setEdgeThickness(edge_id, width);
                    gv->setEdgeDashed(edge_id, dashed);
                    ++edge_id;
                }
                u = v;
            }
            ++i;
        }
        
    }
    gv->rearrange();
}

void MapGraph::drawSpeeds(int fraction, int display) const{
    GraphViewer *gv = createGraphViewer();

    const int width = 5;

    static const std::map<speed_t, string> color_map = {
        {120, "RED"},
        {100, "ORANGE"},
        { 80, "YELLOW"},
        { 60, "GREEN"},
        { 50, "BLACK"},
        { 40, "GRAY"}
    };
    

    double lat_max = -90;
    double lon_min = +180;
    for(const auto &u: nodes){
        lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon);
    }
    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        auto it = color_map.lower_bound(way.getMaxSpeed());
        if(it == color_map.end()) throw invalid_argument("");
        string color = it->second;

        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
                    gv->addNode(v, x, y);
                    drawn_nodes.insert(v);
                }
                if(u != 0){
                    gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
                    gv->setEdgeColor(edge_id, color);
                    gv->setEdgeThickness(edge_id, width);
                    ++edge_id;
                }
                u = v;
            }
            ++i;
        }
        
    }
    gv->rearrange();
}

void MapGraph::drawSCC(int fraction, int display) const{
    GraphViewer *gv = createGraphViewer();
    
    const int width = 5;

    static const std::map<bool, string> color_map = {
        {true , "RED"},
        {false, "GRAY"}
    };

    DUGraph G = (DUGraph)getFullGraph();
    SCCnode *scc = new KosarajuV(new DFS());   
    scc->initialize(&G, station);
    scc->run();

    double lat_max = -90;
    double lon_min = +180;
    for(const auto &u: nodes){
        lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon);
    }
    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){

        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
                    gv->addNode(v, x, y);
                    drawn_nodes.insert(v);
                }
                if(u != 0){
                    string color = color_map.at(scc->is_scc(u) && scc->is_scc(v));
                    gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
                    gv->setEdgeColor(edge_id, color);
                    gv->setEdgeThickness(edge_id, width);
                    ++edge_id;
                }
                u = v;
            }
            ++i;
        }
        
    }
    gv->rearrange();
}

class MapGraph::DistanceHeuristic : public Astar::heuristic_t{
private:
    const std::unordered_map<node_t, MapGraph::pos_t> &nodes;
    MapGraph::pos_t dst_pos;
    double factor;
public:
    DistanceHeuristic(const std::unordered_map<node_t, MapGraph::pos_t> &nodes,
                      MapGraph::pos_t dst_pos,
                      double factor): nodes(nodes), dst_pos(dst_pos), factor(factor){}
    DWGraph::weight_t operator()(node_t u) const{
        auto d = MapGraph::pos_t::getDistanceSI(dst_pos, nodes.at(u));
        return d*factor;
    }
};

void MapGraph::drawPath(int fraction, int display, node_t src, node_t dst, bool visited) const{
    GraphViewer *gv = createGraphViewer();

    DWGraph G = getFullGraph();

    std::vector<std::string> name({
        "Dijkstra's algorithm with early stop",
        "A* algorithm, " + std::to_string(int(120*SPEED_REDUCTION_FACTOR)) +"km/h time estimate [best-performance admissible heuristic]",
        "A* algorithm, 70km/h",
        "A* algorithm, 50km/h",
        "A* algorithm, 30km/h"
    });

    std::vector<ShortestPath*> shortestPaths({
        new Astar(),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(120*KMH_TO_MS*SPEED_REDUCTION_FACTOR))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(70*KMH_TO_MS))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(50*KMH_TO_MS))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(30*KMH_TO_MS)))
    });

    std::vector<std::string> pathColor({
        "BLACK",
        "BLACK",
        "MAGENTA",
        "BLUE",
        "CYAN"
    });

    std::vector<std::string> visitedColor({
        "PINK",
        "RED",
        "MAGENTA",
        "BLUE",
        "CYAN"
    });

    std::vector<std::unordered_set<node_t> > paths(shortestPaths.size());

    for(size_t i = 0; i < shortestPaths.size(); ++i){
        shortestPaths[i]->initialize(&G, src, dst);
        shortestPaths[i]->run();
        std::list<node_t> path = shortestPaths[i]->getPath();
        paths[i] = std::unordered_set<node_t>(path.begin(), path.end());
        statistics_t stats = shortestPaths[i]->getStatistics();
        std::cout   << name[i] << " (" << (!visited ? pathColor[i] : visitedColor[i]) << ")\n"
                    << "- Execution time: " << stats.execution_time << " microseconds\n"
                    << "- Analysed nodes: " << stats.analysed_nodes << "\n"
                    << "- Analysed edges: " << stats.analysed_edges << "\n"
                    << "- Total time    : " << shortestPaths[i]->getPathWeight() << " (+" << 100.0*((double)shortestPaths[i]->getPathWeight()/shortestPaths[0]->getPathWeight()-1.0) << "%)\n"
                    << "- Nodes in path : " << paths[i].size() << "\n";
    }

    double lat_min = 90, lat_max = -90;
    double lon_min = +180, lon_max = -180;
    for(const auto &u: nodes){
        lat_min = std::min(lat_min, u.second.lat); lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon); lon_max = std::max(lon_max, u.second.lon);
    }
    double lat = (lat_max+lat_min)/2;
    double lon = (lon_max+lon_min)/2;

    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){

        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat)*COORDMULT;
                    gv->addNode(v, x, y);
                    drawn_nodes.insert(v);
                }
                if(u != 0){
                    string color = "";
                    int width = 4;

                    if(!visited){
                        for(size_t i = 0; i < shortestPaths.size() && color == ""; ++i){
                            if(paths[i].count(u) && paths[i].count(v)){
                                color = pathColor[i];
                                width = 12;
                            }
                        }
                    } else {
                        if(paths[0].count(u) && paths[0].count(v)){
                            color = pathColor[0];
                            width = 12;
                        }
                        for(long i = shortestPaths.size()-1; i >= 0 && color == ""; --i){
                            if(shortestPaths[i]->hasVisited(u) && shortestPaths[i]->hasVisited(v)){
                                color = visitedColor[i];
                            }
                        }
                    }
                    if(color == "") color = "LIGHT_GRAY";

                    gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
                    gv->setEdgeColor(edge_id, color);
                    gv->setEdgeThickness(edge_id, width);
                    ++edge_id;
                    
                }
                u = v;
            }
            ++i;
        }
    }
    gv->rearrange();
}

