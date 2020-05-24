#include "RoutingHeuristic.h"

#include <algorithm>

#include "HeldKarp.h"

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

class weight_func : public TravellingSalesman::weight_function {
private:
    size_t N;
    const ShortestPathAll *shortestPaths = nullptr;
public:
    weight_func(size_t N_, const ShortestPathAll *shortestPaths_){
        N = N_;
        shortestPaths = shortestPaths_;
    }
    DWGraph::weight_t operator()(const std::unordered_multiset<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
        return (N-S.size())*shortestPaths->getPathWeight(u, v);
    }
};

RoutingHeuristic::RoutingHeuristic(weight_t Dt_, TravellingSalesman *tsp_){
    this->Dt = Dt_;
    tsp = tsp_;
}

void RoutingHeuristic::initialize(const std::list<std::pair<Client, node_t> > *clients_, const std::list<Van> *vans_, node_t station_, const ShortestPathAll *shortestPaths_){
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

    {
        node2client.clear();
        for(const auto &c: vclients){
            node2client.insert(std::make_pair(c.second, c.first));
        }
    }
}

void RoutingHeuristic::run(){
    rides.clear();
    while(!clients.empty()){
        Ride r;

        std::pair<weight_t, Van> v = vans.top(); vans.pop();
        r.setVan(v.second);

        weight_t start_time = std::max(v.first, clients.front().first.getArrival());
        weight_t leave_station_time = start_time;
        std::list<node_t> nodes; nodes.push_back(station);
        while(r.getClients().size() < v.second.getCapacity() &&
              !clients.empty() && clients.front().first.getArrival() < start_time+Dt){
            auto c = clients.front(); clients.pop();
            r.addClient(c.first);
            nodes.push_back(c.second);
            leave_station_time = std::max(leave_station_time, c.first.getArrival());
        }

        TravellingSalesman::weight_function *w = new weight_func(nodes.size(), shortestPaths);

        tsp->initialize(&nodes, station, w);
        tsp->run();
        {
            std::list<node_t> tour_list = tsp->getTour();
            std::vector<node_t> tour(tour_list.begin(), tour_list.end());

            weight_t curr_time = leave_station_time;
            r.leaveStation(station, curr_time);
            
            for(size_t i = 1; i < tour.size()-1; ++i){
                const node_t &fr = tour[i-1], &to = tour[i];
                curr_time += shortestPaths->getPathWeight(fr, to);

                auto it = node2client.find(to);
                Client c = it->second;
                node2client.erase(it);

                r.dropClient(c, curr_time);
            }
            curr_time += shortestPaths->getPathWeight(tour[tour.size()-2], station);
            r.arriveStation(station, curr_time);

            v.first = curr_time;
        }

        rides.push_back(r);

        delete w;

        vans.push(v);
    }
}

const std::vector< Ride >& RoutingHeuristic::getGroups() const{
    return rides;
}
