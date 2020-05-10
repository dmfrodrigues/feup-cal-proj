#include "graphviewer.h"
#include "MapGraph.h"

int main(){
    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineVertexColor("WHITE");
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.draw(gv);
    gv->rearrange();
    return 0;
}
