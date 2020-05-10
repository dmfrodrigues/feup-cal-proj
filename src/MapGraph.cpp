#include "MapGraph.h"

#include <fstream>
#include <unordered_set>
#include <map>

#define COORDMULT 50000

MapGraph::speed_t MapGraph::way_t::getMaxSpeed() const{
    if(speed != -1) return speed;
    switch(edgeType){
        case edge_type_t::MOTORWAY   : return 120;
        case edge_type_t::TRUNK      : return 100;
        case edge_type_t::PRIMARY    : return  90;
        case edge_type_t::SECONDARY  : return  50;
        case edge_type_t::TERTIARY   : return  50;
        case edge_type_t::ROAD       : return  50;
        case edge_type_t::RESIDENTIAL: return  50;
        case edge_type_t::SLOW       : return  20;
        default: throw invalid_argument("");
    }
}

MapGraph::MapGraph(const std::string &path){
    {
        ifstream is(path + ".nodes");
        size_t numberNodes; is >> numberNodes;
        for(size_t i = 0; i < numberNodes; ++i){
            DWGraph::node_t id; pos_t p; is >> id >> p.lat >> p.lon;
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
                DWGraph::node_t id; is >> id;
                way.nodes.push_back(id);
            }
            ways.push_back(way);
        }
    }
}

void MapGraph::drawRoads(GraphViewer *gv, int fraction, int display) const{

    static const std::unordered_map<edge_type_t, Display> display_map = {
        {edge_type_t::MOTORWAY   , Display::MOTORWAY   },
        {edge_type_t::TRUNK      , Display::TRUNK      },
        {edge_type_t::PRIMARY    , Display::PRIMARY    },
        {edge_type_t::SECONDARY  , Display::SECONDARY  },
        {edge_type_t::TERTIARY   , Display::TERTIARY   },
        {edge_type_t::ROAD       , Display::ROAD       },
        {edge_type_t::RESIDENTIAL, Display::RESIDENTIAL},
        {edge_type_t::SLOW       , Display::SLOW       }
    };
    static const std::unordered_map<edge_type_t, bool> dashed_map = {
        {edge_type_t::MOTORWAY   , false},
        {edge_type_t::TRUNK      , false},
        {edge_type_t::PRIMARY    , false},
        {edge_type_t::SECONDARY  , false},
        {edge_type_t::TERTIARY   , false},
        {edge_type_t::ROAD       , false},
        {edge_type_t::RESIDENTIAL, false},
        {edge_type_t::SLOW       , true }
    };
    static const std::unordered_map<edge_type_t, int> width_map = {
        {edge_type_t::MOTORWAY   , 10},
        {edge_type_t::TRUNK      , 10},
        {edge_type_t::PRIMARY    ,  7},
        {edge_type_t::SECONDARY  ,  7},
        {edge_type_t::TERTIARY   ,  5},
        {edge_type_t::ROAD       ,  5},
        {edge_type_t::RESIDENTIAL,  5},
        {edge_type_t::SLOW       ,  5}
    };
    static const std::unordered_map<edge_type_t, string> color_map = {
        {edge_type_t::MOTORWAY   , "RED"},
        {edge_type_t::TRUNK      , "PINK"},
        {edge_type_t::PRIMARY    , "ORANGE"},
        {edge_type_t::SECONDARY  , "YELLOW"},
        {edge_type_t::TERTIARY   , "GRAY"},
        {edge_type_t::ROAD       , "GRAY"},
        {edge_type_t::RESIDENTIAL, "GRAY"},
        {edge_type_t::SLOW       , "GRAY"}
    };
    

    double lat_max = -90;
    double lon_min = +180;
    for(const auto &u: nodes){
        lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon);
    }
    std::unordered_set<DWGraph::node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        string color = color_map.at(way.edgeType);
        int width = width_map.at(way.edgeType);
        bool dashed = dashed_map.at(way.edgeType);
        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        DWGraph::node_t u = 0;
        size_t i = 0;
        for(const DWGraph::node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
                    gv->addNode(v, x, y);
                    gv->setVertexSize(v, 1);
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
}

void MapGraph::drawSpeeds(GraphViewer *gv, int fraction, int display) const{

    static const std::unordered_map<edge_type_t, Display> display_map = {
        {edge_type_t::MOTORWAY   , Display::MOTORWAY   },
        {edge_type_t::TRUNK      , Display::TRUNK      },
        {edge_type_t::PRIMARY    , Display::PRIMARY    },
        {edge_type_t::SECONDARY  , Display::SECONDARY  },
        {edge_type_t::TERTIARY   , Display::TERTIARY   },
        {edge_type_t::ROAD       , Display::ROAD       },
        {edge_type_t::RESIDENTIAL, Display::RESIDENTIAL},
        {edge_type_t::SLOW       , Display::SLOW       }
    };
    
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
    std::unordered_set<DWGraph::node_t> drawn_nodes;
    size_t edge_id = 0;
    for(const way_t &way: ways){
        auto it = color_map.lower_bound(way.getMaxSpeed());
        if(it == color_map.end()) throw invalid_argument("");
        string color = it->second;

        bool draw = display & display_map.at(way.edgeType);

        if(!draw) continue;

        DWGraph::node_t u = 0;
        size_t i = 0;
        for(const DWGraph::node_t &v: way.nodes){
            if(i%fraction == 0 || i == way.nodes.size()-1){
                if(drawn_nodes.find(v) == drawn_nodes.end()){
                    long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
                    long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
                    gv->addNode(v, x, y);
                    gv->setVertexSize(v, 1);
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
}

