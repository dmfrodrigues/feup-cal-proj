#ifndef MAPGRAPH_H_INCLUDED
#define MAPGRAPH_H_INCLUDED

#include "DWGraph.h"

class MapGraph {
private:
    DWGraph G;
    DWGraph Gshort;
public:
    MapGraph(const std::string &path);
    void draw(GraphViewer *gv) const;
}

#endif //MAPGRAPH_H_INCLUDED
