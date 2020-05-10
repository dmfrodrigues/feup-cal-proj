#include "graphviewer.h"
#include "MapGraph.h"

void view(int argc, const char *argv[]){
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineVertexColor("WHITE");
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.draw(gv, fraction, display);
    gv->rearrange();
}

int main(int argc, char *argv[]){
    if(string(argv[1]) == "view") view(argc, (const char **)argv);
    return 0;
}
