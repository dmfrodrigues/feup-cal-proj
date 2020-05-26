#ifndef VEHICLEROUTING_H_INCLUDED
#define VEHICLEROUTING_H_INCLUDED

#include "Client.h"
#include "Van.h"
#include "Ride.h"
#include "DWGraph.h"
#include "ShortestPathAll.h"

#include <list>
#include <vector>

/**
 * @brief Interface for Vehicle Routing Problem related classes 
 * 
 */
class VehicleRouting {
public:

    virtual ~VehicleRouting();

    /**
     * @brief Initializes data members that are required for the execution
     * 
     * @param clients           List of clients
     * @param vans              List of vans
     * @param station           Node of the station
     * @param shortestPaths     Shortest Paths
     */
    virtual void initialize(const std::list<std::pair<Client, DWGraph::node_t> > *clients, const std::list<Van> *vans, DWGraph::node_t station, const ShortestPathAll *shortestPaths) = 0;
    
    /**
     * @brief Executes the algorithm
     * 
     */
    virtual void run() = 0;

    virtual statistics_t getStatistics() const = 0;

    virtual const std::vector< Ride >& getGroups() const = 0;
};

#endif //VEHICLEROUTING_H_INCLUDED
