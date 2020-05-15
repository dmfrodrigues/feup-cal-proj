#include "graphviewer.h"
#include "MapGraph.h"

void view(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawRoads(fraction, display);
}

void speed(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawSpeeds(fraction, display);
}

void scc(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawSCC(fraction, display);
}

void path(int argc, const char *argv[], const MapGraph &M){
    if(argc != 6 && argc != 7) throw invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);
    DWGraph::node_t sour = atoll(argv[4]);
    DWGraph::node_t dest = atoll(argv[5]);
    bool visited = (argc > 6 && string(argv[6]) == "-v");

    M.drawPath(fraction, display, sour, dest, visited);
}

int main(int argc, char *argv[]){
    try {
        if(argc < 2) throw invalid_argument("at least one argument must be provided");
        MapGraph M("map/processed/AMP");
        if(string(argv[1]) == "view" ) view (argc, const_cast<const char **>(argv), M);
        if(string(argv[1]) == "speed") speed(argc, const_cast<const char **>(argv), M);
        if(string(argv[1]) == "scc"  ) scc  (argc, const_cast<const char **>(argv), M);
        if(string(argv[1]) == "path" ) path (argc, const_cast<const char **>(argv), M);
    } catch(const invalid_argument &e){
        cout << "Caught exception: " << e.what() << "\n";
        cout << "Usage: ./main (view | speed | scc) FRACTION FLAGS\n"
                "       ./main path FRACTION FLAGS [-v]\n";
        return EXIT_FAILURE;
    }
    return 0;
}
