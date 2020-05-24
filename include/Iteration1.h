#ifndef ITERATION1_H_INCLUDED
#define ITERATION1_H_INCLUDED

#include "Iteration.h"
#include "Van.h"
#include "Client.h"

class Iteration1 : public Iteration {
private:
    const MapGraph *M = nullptr;
    std::string vans_path, clients_path, rides_path;
    std::list<Van> vans;
    std::list< std::pair<Client, DWGraph::node_t> > clients;
public:
    Iteration1();
    void initialize(const MapGraph *M, const std::string &vans_path, const std::string &clients_path, const std::string &rides_path);
    void run();
};

#endif //ITERATION1_H_INCLUDED
