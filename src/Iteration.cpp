#include "Iteration.h"

#include <fstream>

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

Iteration::~Iteration(){}

const MapGraph* Iteration::getM() const{ return M; }

const std::list<Van>& Iteration::getVans() const{ return vans; }

const std::list< std::pair<Client, node_t> >& Iteration::getClients() const{ return clients; }

const std::string& Iteration::getRidesPath() const{ return rides_path; }

void Iteration::initialize(const MapGraph *M_, const std::string &vans_path_, const std::string &clients_path_, const std::string &rides_path_){
    this->M            = M_;
    this->vans_path    = vans_path_;
    this->clients_path = clients_path_;
    this->rides_path   = rides_path_;

    // Vans
    vans.clear();{
        std::ifstream is(vans_path);
        size_t numVans; is >> numVans;
        for(size_t i = 0; i < numVans; ++i){
            Van v; is >> v;
            vans.push_back(v);
        }
    }

    // Clients
    clients.clear();{
        std::ifstream is(clients_path);
        size_t numClients; is >> numClients;
        for(size_t i = 0; i < numClients; ++i){
            Client c; is >> c;
            node_t client_node = M->getClosestNode(c.getDest());
            clients.push_back(std::make_pair(c, client_node));
        }
    }
}

void Iteration::printRides(const std::vector<Ride> &rides) const{
    std::ofstream os(getRidesPath());
    os << rides.size() << "\n";
    for(const Ride &r: rides){
        os << r << "\n";
    }
}
