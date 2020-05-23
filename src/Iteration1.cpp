#include "Iteration1.h"

#include "Van.h"
#include "Client.h"

#include "RoutingHeuristic.h"
#include "Dijkstra.h"

#include <fstream>

#define MIN_TO_MICROS (60*1000000)

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

Iteration1::Iteration1(){}

void Iteration1::initialize(const MapGraph *M_, const std::string &vans_path_, const std::string &clients_path_, const std::string &rides_path_){
    this->M            = M_;
    this->vans_path    = vans_path_;
    this->clients_path = clients_path_;
    this->rides_path   = rides_path_;
}

std::list<Van> getVans(const std::string &vans_path){
    std::list<Van> vans;
    std::ifstream is(vans_path);
    size_t numVans; is >> numVans;
    for(size_t i = 0; i < numVans; ++i){
        Van v; is >> v;
        vans.push_back(v);
    }
    return vans;
}

void Iteration1::run(){
    std::list<Van> vans = getVans(vans_path);
    std::list< std::pair<Client, node_t> > clients;{
        std::ifstream is(clients_path);
        size_t numClients; is >> numClients;
        for(size_t i = 0; i < numClients; ++i){
            Client c; is >> c;
            node_t client_node = M->getClosestNode(c.getDest());
            clients.push_back(std::make_pair(c, client_node));
        }
    }

    DWGraph::DWGraph G = M->getConnectedGraph();

    std::unordered_map<node_t, const ShortestPathOneMany*> shortestPaths;{
        ShortestPathOneMany *sp = new Dijkstra();
        sp->initialize(&G, M->getStationNode());
        sp->run();
        shortestPaths[M->getStationNode()] = sp;

        for(const auto &p: clients){
            sp = new Dijkstra();
            sp->initialize(&G, p.second);
            sp->run();
            shortestPaths[p.second] = sp;
        }
    }

    VehicleRouting *vrp = new RoutingHeuristic(20*MIN_TO_MICROS);

    vrp->initialize(&clients, &vans, M->getStationNode(), shortestPaths);
    vrp->run();

    {
        std::vector< Ride > rides = vrp->getGroups();
        std::ofstream os(rides_path);
        os << rides.size() << "\n";
        for(const Ride &r: rides){
            os << r << "\n";
        }
    }
    
    delete vrp;
}
