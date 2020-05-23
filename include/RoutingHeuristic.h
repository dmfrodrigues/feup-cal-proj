#ifndef ROUTINGHEURISTIC_H_INCLUDED
#define ROUTINGHEURISTIC_H_INCLUDED

#include "VehicleRouting.h"

#include "DWGraph.h"
#include <queue>
#include <map>

class RoutingHeuristic : public VehicleRouting {
private:
    typedef std::priority_queue<std::pair<DWGraph::weight_t, Van>,
                    std::vector<std::pair<DWGraph::weight_t, Van>>,
                   std::greater<std::pair<DWGraph::weight_t, Van>>> min_priority_queue;

    DWGraph::weight_t Dt;
    DWGraph::node_t station;
    std::queue<std::pair<Client, DWGraph::node_t> > clients;
    std::multimap<DWGraph::node_t, Client> node2client;
    min_priority_queue vans;
    std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> shortestPaths;
    std::vector<Ride> rides;
public:
    RoutingHeuristic(DWGraph::weight_t Dt);
    void initialize(const std::list<std::pair<Client, DWGraph::node_t> > *clients, const std::list<Van> *vans, DWGraph::node_t station, const std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> shortestPaths);
    void run();
    const std::vector< Ride >& getGroups() const;
};

#endif //ROUTINGHEURISTIC_H_INCLUDED
