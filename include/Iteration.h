#ifndef ITERATION_H_INCLUDED
#define ITERATION_H_INCLUDED

#include <string>

#include "MapGraph.h"
#include "Van.h"
#include "Client.h"

class Iteration {
private:
    const MapGraph *M = nullptr;
    std::string vans_path, clients_path, rides_path;
    std::list<Van> vans;
    std::list< std::pair<Client, DWGraph::node_t> > clients;
protected:
    const MapGraph *getM() const;
    const std::list<Van>& getVans() const;
    const std::list< std::pair<Client, DWGraph::node_t> >& getClients() const;
    const std::string& getRidesPath() const;
public:
    virtual ~Iteration();
    virtual void initialize(const MapGraph *M, const std::string &vans_path, const std::string &clients_path, const std::string &rides_path) final;
    virtual void run() = 0;
};

#endif //ITERATION_H_INCLUDED
