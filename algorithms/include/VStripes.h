#ifndef VSTRIPES_H_INCLUDED
#define VSTRIPES_H_INCLUDED

#include "ClosestPoint.h"

#include <vector>
#include <set>

class VStripes: public ClosestPoint{
private:
    static bool compx(const coord_t &p1, const coord_t &p2);
    static bool compy(const coord_t &p1, const coord_t &p2);
    typedef bool (*comp)(const coord_t &p1, const coord_t &p2);

    const coord_t::deg_t Delta;
    const coord_t::deg_t INF = 1000000000000;
    std::vector<coord_t::deg_t> lim;
    std::vector< std::set<coord_t, comp> > sets;
public:
    VStripes(coord_t::deg_t Delta);
    void initialize(const std::list<coord_t> &points);
    void run();
    coord_t getClosestPoint(const coord_t p) const;
};

#endif //VSTRIPES_H_INCLUDED
