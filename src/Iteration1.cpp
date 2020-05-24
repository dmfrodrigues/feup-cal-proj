#include "Iteration1.h"

#include "RoutingHeuristic.h"
#include "Dijkstra.h"
#include "HeldKarp.h"

#include <fstream>

#define MIN_TO_MICROS (60*1000000)

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

Iteration1::Iteration1(){}

void Iteration1::run(){

    DWGraph::DWGraph G = getM()->getConnectedGraph();

    std::unordered_map<node_t, const ShortestPathOneMany*> shortestPaths;{
        ShortestPathOneMany *sp = new Dijkstra();
        sp->initialize(&G, getM()->getStationNode());
        sp->run();
        shortestPaths[getM()->getStationNode()] = sp;

        for(const auto &p: getClients()){
            sp = new Dijkstra();
            sp->initialize(&G, p.second);
            sp->run();
            shortestPaths[p.second] = sp;
        }
    }

    VehicleRouting *vrp = new RoutingHeuristic(20*MIN_TO_MICROS, new HeldKarp());

    vrp->initialize(&getClients(), &getVans(), getM()->getStationNode(), shortestPaths);
    vrp->run();

    {
        std::vector< Ride > rides = vrp->getGroups();
        Iteration::printRides(rides);
    }
    
    delete vrp;
}
