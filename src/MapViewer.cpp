#include "MapViewer.h"

MapViewer::MapViewer(window_t w, window_t h): GraphViewer(w, h, false){
    GraphViewer::defineEdgeCurved(false);
    GraphViewer::defineVertexSize(0);
    GraphViewer::createWindow(w, h);
}
