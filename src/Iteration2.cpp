#include "Iteration2.h"

#include "RoutingHeuristic.h"
#include "Dijkstra.h"
#include "NearestNeighbour.h"

#include <fstream>

#define MIN_TO_MICROS (60*1000000)

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

void Iteration2::run(){
    std::cout << "Getting connected graph..." << std::endl;
    DWGraph::DWGraph G = getM()->getConnectedGraph();

    std::cout << "Getting shortest paths..." << std::endl;
    std::unordered_set<node_t> nodes({getM()->getStationNode()});
    for(const auto &p: getClients()) nodes.insert(p.second);
    ShortestPathAll::FromOneMany sp(new Dijkstra(), 8);
    sp.initialize(&G, nodes);
    sp.run();

    std::cout << "Solving vehicle routing problem..." << std::endl;
    VehicleRouting *vrp = new RoutingHeuristic(20*MIN_TO_MICROS, new NearestNeighbour());

    vrp->initialize(&getClients(), &getVans(), getM()->getStationNode(), &sp);
    vrp->run();

    {
        std::vector< Ride > rides = vrp->getGroups();
        Iteration::printRides(rides);
    }
    
    delete vrp;
}
