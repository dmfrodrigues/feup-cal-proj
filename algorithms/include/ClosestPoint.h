#ifndef CLOSESTPOINT_H_INCLUDED
#define CLOSESTPOINT_H_INCLUDED

#include <list>
#include "coord.h"

class ClosestPoint {
public:
    virtual void initialize(const std::list<coord_t> &points) = 0;
    virtual void run() = 0;
    virtual coord_t getClosestPoint(coord_t p) const = 0;
};

#endif //CLOSESTPOINT_H_INCLUDED
