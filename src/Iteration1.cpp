#include "Iteration1.h"

#include "RoutingHeuristic.h"
#include "Dijkstra.h"
#include "HeldKarp.h"

#include <fstream>

#define MIN_TO_MICROS (60*1000000)

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

void Iteration1::run(){
    std::cout << "Getting connected graph..." << std::endl;
    DWGraph::DWGraph G = getM()->getConnectedGraph();

    std::cout << "Getting shortest paths..." << std::endl;
    const int nthreads = std::thread::hardware_concurrency();
    std::cout << "    Using " << nthreads << " threads" << std::endl;
    std::unordered_set<node_t> nodes({getM()->getStationNode()});
    for(const auto &p: getClients()) nodes.insert(p.second);
    ShortestPathOneMany *sp1m = new Dijkstra();
    ShortestPathAll::FromOneMany *sp = new ShortestPathAll::FromOneMany(sp1m, nthreads);
    sp->initialize(&G, nodes);
    sp->run();
    std::cout << "    Took " << sp->getStatistics().execution_time << " micros" << std::endl;

    std::cout << "Solving vehicle routing problem..." << std::endl;
    TravellingSalesman *tsp = new HeldKarp();
    VehicleRouting *vrp = new RoutingHeuristic(20*MIN_TO_MICROS, tsp);
    vrp->initialize(&getClients(), &getVans(), getM()->getStationNode(), sp);
    vrp->run();
    std::cout << "    Took " << vrp->getStatistics().execution_time << " micros" << std::endl;

    {
        std::vector< Ride > rides = vrp->getGroups();
        Iteration::printRides(rides);
    }

    delete vrp;
    delete sp;
    delete sp1m;
}
