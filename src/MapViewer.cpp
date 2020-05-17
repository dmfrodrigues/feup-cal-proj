#include "MapViewer.h"

#define COORDMULT               50000       // Multiply coordinates to get integer positions

MapViewer::MapViewer(window_t w, window_t h, coord_t min_, coord_t max_):
    GraphViewer(w, h, false), min(min_), max(max_), mean((min_+max_)/2){
    if(!GraphViewer::defineEdgeCurved(false))   throw std::runtime_error("");
    if(!GraphViewer::defineVertexSize(0))       throw std::runtime_error("");
    if(!GraphViewer::createWindow(w, h))        throw std::runtime_error("");
}

void MapViewer::addNode(node_t i, coord_t c){
    window_t x = (window_t)(double)(+(c.getLon() - mean.getLon())*COORDMULT);
    window_t y = (window_t)(double)(-(c.getLat() - mean.getLat())*COORDMULT);
    if(!GraphViewer::addNode(nodes[i] = next_id++, x, y))   throw std::runtime_error("");
}

void MapViewer::addEdge(edge_t i, node_t u, node_t v, int edge_type, string color, window_t w, bool dashed){
    if(!GraphViewer::addEdge((int)i, nodes[u], nodes[v], edge_type))    throw std::runtime_error("");
    if(!GraphViewer::setEdgeColor((int)i, color))                       throw std::runtime_error("");
    if(!GraphViewer::setEdgeThickness((int)i, w))                       throw std::runtime_error("");
    if(!GraphViewer::setEdgeDashed((int)i, dashed))                     throw std::runtime_error("");
}

void MapViewer::rearrange(){
    if(!GraphViewer::rearrange()) throw std::runtime_error("");
}
