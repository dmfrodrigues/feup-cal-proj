#ifndef ITERATION_H_INCLUDED
#define ITERATION_H_INCLUDED

#include <string>

#include "MapGraph.h"

class Iteration {
public:
    virtual ~Iteration();
    virtual void initialize(const MapGraph *M, const std::string &vans_path, const std::string &clients_path, const std::string &rides_path) = 0;
    virtual void run() = 0;
};

#endif //ITERATION_H_INCLUDED
