#include "MapGraph.h"

#include <fstream>

#define COORDMULT 20000

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

void MapGraph::draw(GraphViewer *gv) const{
    double lat_max = -90;
    double lon_min = +180;
    for(const auto &u: nodes){
        lat_max = std::max(lat_max, u.second.lat);
        lon_min = std::min(lon_min, u.second.lon);
    }
    size_t edge_id = 0;
    for(const way_t &way: ways){
        string color;
        bool draw;
        switch(way.edgeType){
            case edge_type_t::Motorway      : draw = true ; color = "red"; break;
            case edge_type_t::Trunk         : draw = true ; color = "pink"; break;
            case edge_type_t::Residential   : draw = false; color = "green"; break;
            case edge_type_t::Road          : draw = false; color = "black"; break;
            case edge_type_t::Slow          : draw = false; color = "gray"; break;
            case edge_type_t::No: throw invalid_argument("edge type cannot be 'No'");
        }

        if(!draw) continue;

        /*
        long long x, y;
        
        DWGraph::node_t u = *way.nodes.begin();
        x = +(nodes.at(u).lon-lon_min)*COORDMULT;
        y = -(nodes.at(u).lat-lat_max)*COORDMULT;
        gv->addNode(u, x, y);

        DWGraph::node_t v = *way.nodes.rbegin();
        x = +(nodes.at(v).lon-lon_min)*COORDMULT;
        y = -(nodes.at(v).lat-lat_max)*COORDMULT;
        gv->addNode(v, x, y);

        gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
        gv->setEdgeColor(edge_id, color);
        ++edge_id;
        */
        
        DWGraph::node_t u = 0;
        for(const DWGraph::node_t &v: way.nodes){
            long long x = +(nodes.at(v).lon-lon_min)*COORDMULT;
            long long y = -(nodes.at(v).lat-lat_max)*COORDMULT;
            gv->addNode(v, x, y);
            gv->setVertexSize(v, 1);
            if(u != 0){
                gv->addEdge(edge_id, u, v, EdgeType::UNDIRECTED);
                gv->setEdgeColor(edge_id, color);
                ++edge_id;
            }
            u = v;
        }
        
    }
    /*
    for(const auto &u: nodes){
        long long x = (u.second.lon-lon_min)*COORDMULT;
        long long y = -(u.second.lat-lat_max)*COORDMULT;
        gv->addNode(u.first, x, y);
        gv->setVertexSize(u.first, 1);
        ++i;
    }
    */
}
