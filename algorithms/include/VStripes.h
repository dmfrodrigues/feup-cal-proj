#ifndef VSTRIPES_H_INCLUDED
#define VSTRIPES_H_INCLUDED

#include "ClosestPoint.h"

#include <vector>
#include <set>

/**
 * @brief VStripes algorithm for Closest Point
 * 
 */
class VStripes: public ClosestPoint{
private:
    /**
     * @brief Compares two sets of coords using longitude
     * 
     * @param p1        First Point
     * @param p2        Second Point
     * @return true     If p1 is at the left of p2 (p1 long < p2 long)
     * @return false    Otherwise
     */
    static bool compx(const coord_t &p1, const coord_t &p2);

    /**
     * @brief Compares two sets of coords using latitude
     * 
     * @param p1        First Point
     * @param p2        Second Point
     * @return true     If p1 is under p2 (p1 lat < p2 lat)
     * @return false    Otherwise
     */
    static bool compy(const coord_t &p1, const coord_t &p2);
    typedef bool (*comp)(const coord_t &p1, const coord_t &p2);

    const coord_t::deg_t Delta;
    const coord_t::deg_t INF = 1000000000000;
    std::vector<coord_t::deg_t> lim;
    std::vector< std::set<coord_t, comp> > sets;
public:
    /**
     * @brief Construct from degrees
     * 
     * @param Delta value in degress
     */
    VStripes(coord_t::deg_t Delta);

    /**
     * @brief Initializes data members
     * 
     * @param points List of provided Points
     */
    void initialize(const std::list<coord_t> &points);

    /**
     * @brief Executes the algorithm
     * 
     */
    void run();

    coord_t getClosestPoint(const coord_t p) const;
};

#endif //VSTRIPES_H_INCLUDED
