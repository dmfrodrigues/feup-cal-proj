#include "graphviewer.h"

class MapViewer : private GraphViewer {
public:
    typedef int window_t;
    typedef long long node_t;
    MapViewer(window_t w, window_t h);
};
