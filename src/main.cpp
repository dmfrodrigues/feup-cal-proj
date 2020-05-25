#include <fstream>

#include "graphviewer.h"
#include "MapGraph.h"
#include "Iteration1.h"
#include "Iteration2.h"

void view(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw std::invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawRoads(fraction, display);
}

void speed(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw std::invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawSpeeds(fraction, display);
}

void scc(int argc, const char *argv[], const MapGraph &M){
    if(argc != 4) throw std::invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);

    M.drawSCC(fraction, display);
}

void path(int argc, const char *argv[], const MapGraph &M){
    if(argc != 6 && argc != 7 && argc != 8 && argc != 9) throw std::invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);
    if(argc == 6 || argc == 7){
        DWGraph::node_t sour = atoll(argv[4]);
        DWGraph::node_t dest = atoll(argv[5]);
        bool visited = (argc > 6 && std::string(argv[6]) == "-v");

        M.drawPath(fraction, display, sour, dest, visited);
    } else {
        coord_t sour(atof(argv[4]), atof(argv[5]));
        coord_t dest(atof(argv[6]), atof(argv[7]));
        bool visited = (argc > 8 && std::string(argv[8]) == "-v");

        M.drawPath(fraction, display, sour, dest, visited);
    }
}

void reduced(int, const char *[], const MapGraph &M){
    M.drawReduced();
}

void ride(int argc, const char *argv[], const MapGraph &M){
    if(argc != 6) throw std::invalid_argument("invalid number of arguments");
    int fraction = atoi(argv[2]);
    int display  = atoi(argv[3]);
    std::string rides_path = argv[4];
    size_t ride_i = atol(argv[5]);

    Ride r;{
        std::ifstream is(rides_path);
        size_t num_rides; is >> num_rides;
        if(ride_i >= num_rides) throw std::invalid_argument("index too large");
        Ride tmp;
        for(size_t i = 0; i < ride_i; ++i) is >> tmp;
        is >> r;
    }
    
    std::cout << "Ride starts at " << r.getStartTime() << " and ends at " << r.getEndTime() << std::endl;

    M.drawRide(r);
}

void iteration1(int argc, const char *argv[], const MapGraph &M){
    if(argc != 5) throw std::invalid_argument("invalid number of arguments");
    
    std::string vans_path = argv[2];
    std::string clients_path = argv[3];
    std::string rides_path = argv[4];

    Iteration *it = new Iteration1();
    it->initialize(&M, vans_path, clients_path, rides_path);
    it->run();

    delete it;
}

void iteration2(int argc, const char *argv[], const MapGraph &M){
    if(argc != 5) throw std::invalid_argument("invalid number of arguments");
    
    std::string vans_path = argv[2];
    std::string clients_path = argv[3];
    std::string rides_path = argv[4];

    Iteration *it = new Iteration2();
    it->initialize(&M, vans_path, clients_path, rides_path);
    it->run();

    delete it;
}

int main(int argc, char *argv[]){
    try {
        if(argc < 2) throw std::invalid_argument("at least one argument must be provided");
        MapGraph M("map/processed/AMP");
        std::string opt = argv[1];
        if(opt == "view"      ) view      (argc, const_cast<const char **>(argv), M);
        if(opt == "speed"     ) speed     (argc, const_cast<const char **>(argv), M);
        if(opt == "scc"       ) scc       (argc, const_cast<const char **>(argv), M);
        if(opt == "path"      ) path      (argc, const_cast<const char **>(argv), M);
        if(opt == "reduced"   ) reduced   (argc, const_cast<const char **>(argv), M);
        if(opt == "ride"      ) ride      (argc, const_cast<const char **>(argv), M);
        if(opt == "iteration1") iteration1(argc, const_cast<const char **>(argv), M);
        if(opt == "iteration2") iteration2(argc, const_cast<const char **>(argv), M);
    } catch(const std::invalid_argument &e){
        std::cout << "Caught exception: " << e.what() << "\n";
        std::cout << "Usage: ./main (view | speed | scc) FRACTION FLAGS\n"
                     "       ./main path FRACTION FLAGS [-v]\n";
        return EXIT_FAILURE;
    }
    return 0;
}
