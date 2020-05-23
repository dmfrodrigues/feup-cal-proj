#ifndef VEHICLEROUTING_H_INCLUDED
#define VEHICLEROUTING_H_INCLUDED

#include "Client.h"
#include "Van.h"
#include "Ride.h"
#include "DWGraph.h"
#include "ShortestPathOneMany.h"

#include <list>
#include <vector>

class VehicleRouting {
public:
    virtual ~VehicleRouting();
    virtual void initialize(const std::list<std::pair<Client, DWGraph::node_t> > *clients, const std::list<Van> *vans, DWGraph::node_t station, const std::unordered_map<DWGraph::node_t, const ShortestPathOneMany*> shortestPaths) = 0;
    virtual void run() = 0;
    virtual const std::vector< Ride >& getGroups() const = 0;
};

#endif //VEHICLEROUTING_H_INCLUDED
