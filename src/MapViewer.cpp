#include "MapViewer.h"

MapViewer::MapViewer(window_t w, window_t h): GraphViewer(w, h, false){
    if(!GraphViewer::defineEdgeCurved(false))   throw std::runtime_error("");
    if(!GraphViewer::defineVertexSize(0))       throw std::runtime_error("");
    if(!GraphViewer::createWindow(w, h))        throw std::runtime_error("");
}
