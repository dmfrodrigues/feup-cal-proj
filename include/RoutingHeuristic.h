#ifndef ROUTINGHEURISTIC_H_INCLUDED
#define ROUTINGHEURISTIC_H_INCLUDED

#include "VehicleRouting.h"
#include "TravellingSalesman.h"

#include "DWGraph.h"
#include <queue>
#include <map>

/**
 * @brief Routing Heuristic 
 * 
 */
class RoutingHeuristic : public VehicleRouting {
private:
    typedef std::priority_queue<std::pair<DWGraph::weight_t, Van>,
                    std::vector<std::pair<DWGraph::weight_t, Van>>,
                   std::greater<std::pair<DWGraph::weight_t, Van>>> min_priority_queue;

    DWGraph::weight_t Dt;
    TravellingSalesman *tsp = nullptr;
    DWGraph::node_t station;
    std::queue<std::pair<Client, DWGraph::node_t> > clients;
    std::multimap<DWGraph::node_t, Client> node2client;
    min_priority_queue vans;
    const ShortestPathAll *shortestPaths = nullptr;
    std::vector<Ride> rides;
public:
    /**
     * @brief Construct from Delta and Travelling Salesman arguments 
     * 
     * @param Dt    Delta (VStripes)
     * @param tsp   Travelling Salesman instance
     */
    RoutingHeuristic(DWGraph::weight_t Dt, TravellingSalesman *tsp);
    
    /**
     * @brief Initializes data members that are required for the execution
     * 
     * @param clients           List of clients
     * @param vans              List of vans
     * @param station           Node of the station
     * @param shortestPaths     Shortest Paths
     */
    void initialize(const std::list<std::pair<Client, DWGraph::node_t> > *clients, const std::list<Van> *vans, DWGraph::node_t station, const ShortestPathAll *shortestPaths);

    /**
     * @brief Executes the algorithm
     * 
     */
    void run();
    const std::vector< Ride >& getGroups() const;
};

#endif //ROUTINGHEURISTIC_H_INCLUDED
