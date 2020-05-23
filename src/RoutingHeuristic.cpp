#include "RoutingHeuristic.h"

#include <algorithm>

#include "HeldKarp.h"

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

class weight_func : public TravellingSalesman::weight_function {
private:
    int N;
    const std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> *shortestPaths = nullptr;
public:
    weight_func(int N_, const std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> *shortestPaths_){
        N = N_;
        shortestPaths = shortestPaths_;
    }
    DWGraph::weight_t operator()(const std::unordered_set<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
        return (N-S.size())*shortestPaths->at(u)->getPathWeight(v);
    }
};

RoutingHeuristic::RoutingHeuristic(weight_t Dt_){
    this->Dt = Dt_;
}

void RoutingHeuristic::initialize(const std::list<std::pair<Client, node_t> > *clients_, const std::list<Van> *vans_, node_t station_, const std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> shortestPaths_){
    std::vector<std::pair<Client, node_t>> vclients(clients_->begin(), clients_->end());
    std::sort(vclients.begin(), vclients.end());
    for(const auto &c: vclients){
        clients.push(c);
    }

    for(const Van &v: *vans_){
        vans.push(std::make_pair(0, v));
    }

    station = station_;

    shortestPaths = shortestPaths_;

    rides.clear();
}

void RoutingHeuristic::run(){
    while(!clients.empty()){
        std::pair<weight_t, Van> v = vans.top(); vans.pop();
        Ride r;
        r.setVan(v.second);
        weight_t start_time = std::max(v.first, clients.front().first.getArrival());

        std::list<node_t> nodes; nodes.push_back(station);

        while(r.getClients().size() < v.second.getCapacity() &&
              !clients.empty() && clients.front().first.getArrival() < start_time+Dt){
            r.addClient(clients.front().first);
            nodes.push_back(clients.front().second);
            clients.pop();
        }

        TravellingSalesman::weight_function *w = new weight_func(nodes.size(), &shortestPaths);

        TravellingSalesman *tsp = new HeldKarp();

        tsp->initialize(&nodes, station, w);
        tsp->run();

        delete tsp;
        delete w;
    }
}

const std::vector< Ride >& RoutingHeuristic::getGroups() const{
    return rides;
}
