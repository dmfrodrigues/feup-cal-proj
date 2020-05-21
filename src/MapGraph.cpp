#include "MapGraph.h"

#include "Astar.h"
#include "KosarajuV.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "ShortestPath.h"
#include "MapViewer.h"
#include "ShortestPathAll.h"
#include "VStripes.h"

#include <fstream>
#include <iomanip>
#include <unordered_set>
#include <map>
#include <vector>

#define COORDMULT               50000       // Multiply coordinates to get integer positions
#define SECONDS_TO_MICROS       1000000     // Convert seconds to milliseconds
#define KMH_TO_MS               (1.0/3.6)   // Convert km/h to m/s
#define SPEED_REDUCTION_FACTOR  0.75        // Reduce speed to account for intense road traffic, and the fact people not always travel at maximum speed 

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

MapGraph::speed_t MapGraph::way_t::getMaxSpeed() const{
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    if(speed != -1) return speed;
    #pragma GCC diagnostic pop

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
        case edge_type_t::NO             : throw std::invalid_argument("");
        default                          : throw std::invalid_argument("");
    }
}

MapGraph::speed_t MapGraph::way_t::getRealSpeed() const{

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    if(speed != -1) return speed*KMH_TO_MS*SPEED_REDUCTION_FACTOR;
    #pragma GCC diagnostic pop

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
        case edge_type_t::NO             : throw std::invalid_argument("");
        default                          : throw std::invalid_argument("");
    }
}

MapGraph::MapGraph(const std::string &path){
    {
        std::ifstream is(path + ".nodes");
        size_t numberNodes; is >> numberNodes;
        for(size_t i = 0; i < numberNodes; ++i){
            coord_t::deg_t lat, lon;
            node_t id; is >> id >> lat >> lon;
            nodes[id] = coord_t(lat, lon);
        }
    }
    {
        std::ifstream is(path + ".edges");
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
    {
        coord_t::deg_t lat_min = 90, lat_max = -90;
        coord_t::deg_t lon_min = +180, lon_max = -180;
        for(const auto &u: nodes){
            lat_min = std::min(lat_min, u.second.getLat()); lat_max = std::max(lat_max, u.second.getLat());
            lon_min = std::min(lon_min, u.second.getLon()); lon_max = std::max(lon_max, u.second.getLon());
        }
        min_coord = coord_t(lat_max, lon_min);
        max_coord = coord_t(lat_min, lon_max);
        mean_coord = (min_coord + max_coord)/2;
    }
}

DWGraph::DWGraph MapGraph::getFullGraph() const{
    DWGraph::DWGraph G;
    for(const auto &p: nodes) G.addNode(p.first);
    for(const way_t &w: ways){
        if(w.nodes.size() < 2) continue;
        auto it1 = w.nodes.begin();
        for(auto it2 = it1++; it1 != w.nodes.end(); ++it1, ++it2){
            auto d = coord_t::getDistanceSI(nodes.at(*it1), nodes.at(*it2));
            double factor = double(SECONDS_TO_MICROS)/(w.getRealSpeed());
            G.addEdge(*it2, *it1, d*factor);
        }
    }
    return G;
}

DWGraph::DWGraph MapGraph::getConnectedGraph() const{
    DWGraph::DWGraph G = getFullGraph();
    DUGraph Gu = (DUGraph)G;
    SCCnode *scc = new KosarajuV(new DFS());
    scc->initialize(&Gu, station);
    scc->run();
    std::list<node_t> nodes_to_remove;
    for(const DUGraph::node_t &u: Gu.getNodes()){
        if(!scc->is_scc(u)){
            nodes_to_remove.push_back(u);
        }
    }
    delete scc;
    G.removeNodes(nodes_to_remove.begin(), nodes_to_remove.end());
    return G;
}

DWGraph::DWGraph MapGraph::getReducedGraph() const{
    DWGraph::DWGraph G = getConnectedGraph();
    std::cout << "Nodes: " << G.getNodes().size() << "\n"
              << "Edges: " << G.getNumberEdges() << "\n";
    
    size_t prev_nodes;
    do{
        prev_nodes = G.getNodes().size();

        DWGraph::DWGraph GT = G.getTranspose();
        auto V = G.getNodes();
        for(const node_t &u: V){
            const auto &desc = G.getAdj(u);
            const auto &pred = GT.getAdj(u);

            // Remove one-way streets
            if(desc.size() == 1 && pred.size() == 1 && desc.begin()->v != pred.begin()->v){
                //cout << "Deleting one-way street through " << u << endl;
                const node_t a = pred.begin()->v;
                const node_t b = desc.begin()->v;
                const weight_t w = pred.begin()->w + desc.begin()->w;
                G.addBestEdge(a, b, w); GT.addBestEdge(b, a, w);
                G.removeNode(u); GT.removeNode(u);
            } else
            if(desc.size() == 2 && pred.size() == 2){
                auto it = desc.begin();
                const DWGraph::Edge ua_f = *(it++); // Edge from u to a in forward notation
                const DWGraph::Edge ub_f = *(it++); // Edge from u to b in forward notation
                const node_t a = ua_f.v;
                const node_t b = ub_f.v;
                const weight_t w_ua = ua_f.w;
                const weight_t w_ub = ub_f.w;
                auto it1 = pred.find(ua_f);
                auto it2 = pred.find(ub_f);
                if(it1 != pred.end() && it2 != pred.end()){
                    const DWGraph::Edge au_b = *it1; // Edge from a to u in backwards notation
                    const DWGraph::Edge bu_b = *it2; // Edge from b to u in backwards notation
                    const weight_t w_au = au_b.w;
                    const weight_t w_bu = bu_b.w;
                    const weight_t w_ab = w_au+w_ub;
                    const weight_t w_ba = w_bu+w_ua;
                    G.addBestEdge(a, b, w_ab); GT.addBestEdge(b, a, w_ab);
                    G.addBestEdge(b, a, w_ba); GT.addBestEdge(a, b, w_ba);
                    G.removeNode(u); GT.removeNode(u);
                }
            }
        }
        std::cout << "Nodes: " << G.getNodes().size() << "\n"
                  << "Edges: " << G.getNumberEdges() << "\n";
    } while(prev_nodes != G.getNodes().size());

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

MapViewer* createMapViewer(coord_t min_coord, coord_t max_coord, int w = 1800, int h = 900){
    MapViewer *gv = new MapViewer(w, h, min_coord, max_coord);
    return gv;
}

void MapGraph::drawRoads(int fraction, int display) const{
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
    static const std::unordered_map<edge_type_t, std::string> color_map = {
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

    MapViewer *gv = createMapViewer(min_coord, max_coord);
    
    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        std::string color = color_map.at(way.edgeType);
        int width = width_map.at(way.edgeType);
        bool dashed = dashed_map.at(way.edgeType);
        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    drawn_nodes.insert(v);
                    gv->addNode(v, nodes.at(v));
                }
                if(u != 0){
                    gv->addEdge(edge_id++, u, v, EdgeType::UNDIRECTED, color, width, dashed);
                }
                u = v;
            }
            ++i;
        }
        
    }
    gv->rearrange();
}

void MapGraph::drawSpeeds(int fraction, int display) const{
    static const int width = 5;
    static const std::map<speed_t, std::string> color_map = {
        {120, "RED"},
        {100, "ORANGE"},
        { 80, "YELLOW"},
        { 60, "GREEN"},
        { 50, "BLACK"},
        { 40, "GRAY"}
    };

    MapViewer *gv = createMapViewer(min_coord, max_coord);

    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        std::string color; {
            auto it = color_map.lower_bound(way.getMaxSpeed());
            if(it == color_map.end()) throw std::invalid_argument("");
            color = it->second;
        }
        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    drawn_nodes.insert(v);
                    gv->addNode(v, nodes.at(v));
                }
                if(u != 0){
                    gv->addEdge(edge_id++, u, v, EdgeType::UNDIRECTED, color, width);
                }
                u = v;
            }
            ++i;
        }
        
    }
    gv->rearrange();
}

void MapGraph::drawSCC(int fraction, int display) const{
    static const int width = 5;
    static const std::map<bool, std::string> color_map = {
        {true , "RED"},
        {false, "GRAY"}
    };

    DWGraph::DWGraph G  = getFullGraph();
    std::unordered_set<node_t> connected_nodes; {
        DWGraph::DWGraph Gu = getConnectedGraph();
        const auto &l = Gu.getNodes();
        connected_nodes = std::unordered_set<node_t>(l.begin(), l.end());
    }

    MapViewer *gv = createMapViewer(min_coord, max_coord);

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
                    drawn_nodes.insert(v);
                    gv->addNode(v, nodes.at(v));
                }
                if(u != 0){
                    std::string color = color_map.at(connected_nodes.count(u) && connected_nodes.count(v));
                    gv->addEdge(edge_id++, u, v, EdgeType::UNDIRECTED, color, width);
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
    const std::unordered_map<node_t, coord_t> &nodes;
    coord_t dst_pos;
    double factor;
public:
    DistanceHeuristic(const std::unordered_map<node_t, coord_t> &nodes_,
                      coord_t dst_pos_,
                      double factor_): nodes(nodes_), dst_pos(dst_pos_), factor(factor_){ std::cout << "factor is " << factor_ << std::endl; }
    weight_t operator()(node_t u) const{
        auto d = coord_t::getDistanceSI(dst_pos, nodes.at(u));
        return d*factor;
    }
};

void MapGraph::drawPath(int fraction, int display, node_t src, node_t dst, bool visited) const{
    DWGraph::DWGraph G = getConnectedGraph();

    std::vector<std::string> name({
        "Dijkstra's algorithm with early stop",
        "A* algorithm, 90km/h",
        "A* algorithm, 70km/h",
        "A* algorithm, 50km/h",
        "A* algorithm, 30km/h"
    });

    std::vector<ShortestPath*> shortestPaths({
        new Astar(),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(90.0*KMH_TO_MS))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(70.0*KMH_TO_MS))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(50.0*KMH_TO_MS))),
        new Astar(new DistanceHeuristic(nodes, nodes.at(dst), double(SECONDS_TO_MICROS)/(30.0*KMH_TO_MS)))
    });

    std::vector<std::string> pathColor({
        "BLACK",
        "RED",
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

    std::cout << std::setfill(' ');
    std::cout << "| Algorithm                                | Colour     | Execution time (micros) | Analysed nodes | Analysed edges | Total time (micros) | Increase in total time | Nodes in path |\n"
              << "|------------------------------------------|------------|-------------------------|----------------|----------------|---------------------|------------------------|---------------|\n";

    for(size_t i = 0; i < shortestPaths.size(); ++i){
        shortestPaths[i]->initialize(&G, src, dst);
        shortestPaths[i]->run();
        std::list<node_t> path = shortestPaths[i]->getPath();
        paths[i] = std::unordered_set<node_t>(path.begin(), path.end());
        statistics_t stats = shortestPaths[i]->getStatistics();
        std::cout   <<  "| " << std::setw(40) << name[i]
                    << " | " << std::setw(10) << (!visited ? pathColor[i] : visitedColor[i])
                    << " | " << std::setw(23) << stats.execution_time
                    << " | " << std::setw(14) << stats.analysed_nodes
                    << " | " << std::setw(14) << stats.analysed_edges
                    << " | " << std::setw(19) << shortestPaths[i]->getPathWeight()
                    << " | " << std::setw(21) << 100.0*((double)shortestPaths[i]->getPathWeight()/shortestPaths[0]->getPathWeight()-1.0) << "%"
                    << " | " << std::setw(13) << paths[i].size() << " |\n";
    }
    /*
    MapViewer *gv = createMapViewer(min_coord, max_coord);

    std::unordered_set<node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){

        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        node_t u = 0;
        size_t i = 0;
        for(const node_t &v: way.nodes){
            if(!G.hasNode(v)) break;
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    drawn_nodes.insert(v);
                    gv->addNode(v, nodes.at(v));
                }
                if(u != 0){
                    std::string color = "";
                    int width = 4;

                    if(!visited){
                        for(size_t j = 0; j < shortestPaths.size() && color == ""; ++j){
                            if (paths[j].count(u) && paths[j].count(v)){
                                color = pathColor[j];
                                width = 12;
                            }
                        }
                    } else {
                        if(paths[0].count(u) && paths[0].count(v)){
                            color = pathColor[0];
                            width = 12;
                        }
                        for(long j = shortestPaths.size()-1; j >= 0 && color == ""; --j){
                            if (shortestPaths[j]->hasVisited(u) && shortestPaths[j]->hasVisited(v)){
                                color = visitedColor[j];
                            }
                        }
                    }
                    if(color == "") color = "LIGHT_GRAY";

                    gv->addEdge(edge_id++, u, v, EdgeType::UNDIRECTED, color, width);
                }
                u = v;
            }
            ++i;
        }
    }
    gv->rearrange();
    */
    for(ShortestPath *p: shortestPaths) delete p;
}

// ./main path 1 255 1160030583 5284172068
void MapGraph::drawPath(int fraction, int display, coord_t src, coord_t dst, bool visited) const{
    DWGraph::DWGraph G = getConnectedGraph();
    std::list<coord_t> nodes_list;
    for(const node_t &u: G.getNodes()) nodes_list.push_back(nodes.at(u));

    ClosestPoint *closestPoint = new VStripes(0.025);
    closestPoint->initialize(nodes_list);
    closestPoint->run();

    coord_t src_closest = closestPoint->getClosestPoint(src);
    coord_t dst_closest = closestPoint->getClosestPoint(dst);

    node_t src_node = DWGraph::INVALID_NODE;
    node_t dst_node = DWGraph::INVALID_NODE;
    
    for(const auto &p: nodes){
        if(p.second == src_closest) src_node = p.first;
        if(p.second == dst_closest) dst_node = p.first;
    }
    if(src_node == DWGraph::INVALID_NODE || dst_node == DWGraph::INVALID_NODE) throw std::invalid_argument("No such node");

    std::cout << "Source      (" << src << ") transformed into node " << src_node << " (" << src_closest << ")" << std::endl;
    std::cout << "Destination (" << dst << ") transformed into node " << dst_node << " (" << dst_closest << ")" << std::endl;

    drawPath(fraction, display, src_node, dst_node, visited);
}

void MapGraph::drawReduced() const{
    DWGraph::DWGraph G = getReducedGraph();

    MapViewer *mv = createMapViewer(min_coord, max_coord);
    long long edge_id = 0;

    const auto &V = G.getNodes();
    for(const node_t &u: V){
        mv->addNode(u, nodes.at(u));
    }
    for(const node_t &u: V){
        for(const DWGraph::Edge &e: G.getAdj(u)){
            mv->addEdge(edge_id++, u, e.v, EdgeType::DIRECTED, "GRAY", 7);
        }
    }

    mv->rearrange();
}
