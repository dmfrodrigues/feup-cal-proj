#include "graphviewer.h"
#include "MapGraph.h"

void view(int argc, const char *argv[]){
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.drawRoads(gv, fraction, display);
    gv->rearrange();
}

void speed(int argc, const char *argv[]){
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.drawSpeeds(gv, fraction, display);
    gv->rearrange();
}

void scc(int argc, const char *argv[]){
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.drawSCC(gv, fraction, display);
    gv->rearrange();
}

void path(int argc, const char *argv[]){
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    GraphViewer *gv = new GraphViewer(1900, 1000, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(0);
    gv->createWindow(1900, 1000);
    MapGraph M("map/processed/AMP");
    M.drawPath(gv, fraction, display, atoll(argv[4]), atoll(argv[5]), argc > 6 && string(argv[6]) == "-v");
    gv->rearrange();
}

int main(int argc, char *argv[]){
    if(string(argv[1]) == "view" ) view (argc, (const char **)argv);
    if(string(argv[1]) == "speed") speed(argc, (const char **)argv);
    if(string(argv[1]) == "scc"  ) scc  (argc, (const char **)argv);
    if(string(argv[1]) == "path" ) path (argc, (const char **)argv);
    return 0;
}
