#include "VStripes.h"

#include <algorithm>

typedef coord_t::deg_t deg_t;

bool VStripes::compx(const coord_t &p1, const coord_t &p2){

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    if(p1.getLon() != p2.getLon()) return (p1.getLon() < p2.getLon());
    #pragma GCC diagnostic pop

    return (p1.getLat() < p2.getLat());
}
bool VStripes::compy(const coord_t &p1, const coord_t &p2){
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    if(p1.getLat() != p2.getLat()) return (p1.getLat() < p2.getLat());
    #pragma GCC diagnostic pop
    
    return (p1.getLon() < p2.getLon());
}

VStripes::VStripes(deg_t Delta_):Delta(Delta_){}

void VStripes::initialize(const std::list<coord_t> &points){
    deg_t lon_min = +180, lon_max = -180;
    for(const coord_t &c: points){
        lon_min = std::min(lon_min, c.getLon());
        lon_max = std::max(lon_max, c.getLon());
    }
    
    lim.clear();
    lim.push_back(lon_min);
    deg_t lon = lon_min;
    while(lim[lim.size()-1] < lon_max){
        lon += Delta;
        lim.push_back(lon);
    }

    sets = std::vector< std::set<coord_t, comp> >(lim.size()-1, std::set<coord_t, comp>(compy));

    for(const coord_t &p: points){
        size_t pos = std::upper_bound(lim.begin(), lim.end(), p.getLon()) - lim.begin() -1;
        sets.at(pos).insert(p);
    }
}

void VStripes::run(){}

coord_t VStripes::getClosestPoint(const coord_t p) const{
    coord_t ret(INF, INF);
    deg_t dist = INF;
    
    ssize_t pos = std::upper_bound(lim.begin(), lim.end(), p.getLon()) - lim.begin() -1;
    pos = std::max(std::min(pos, ssize_t(sets.size())-1), ssize_t(0));
    
    // Using mid
    {
        const std::set<coord_t, comp> &mid = sets.at(pos);
        // Initial attempt to reduce distance
        {
            auto it = mid.lower_bound(p);
            if(it != mid.end  ()){
                deg_t dist_ = coord_t::getDistanceDeg(p, *it);
                if(dist_ < dist){
                    ret = *it;
                    dist = dist_;
                }
            }
            if(it != mid.begin()){
                --it;
                deg_t dist_ = coord_t::getDistanceDeg(p, *it);
                if(dist_ < dist){
                    ret = *it;
                    dist = dist_;
                }
            }
        }
        // Reduce distance with mid
        {
            coord_t south(p.getLat()-dist, p.getLon());
            coord_t north(p.getLat()+dist, p.getLon());
            auto south_it = mid.lower_bound(south);
            auto north_it = mid.upper_bound(north);
            for(auto it = south_it; it != north_it; ++it){
                deg_t dist_ = coord_t::getDistanceDeg(p, *it);
                if(dist_ < dist){
                    ret = *it;
                    dist = dist_;
                }
            }
        }
    }
    // Reduce distance with left
    if(pos-1 >= 0){
        const std::set<coord_t, comp> &left = sets.at(pos-1);
        coord_t south(p.getLat()-dist, p.getLon());
        coord_t north(p.getLat()+dist, p.getLon());
        auto south_it = left.lower_bound(south);
        auto north_it = left.upper_bound(north);
        for(auto it = south_it; it != north_it; ++it){
            deg_t dist_ = coord_t::getDistanceDeg(p, *it);
            if(dist_ < dist){
                ret = *it;
                dist = dist_;
            }
        }
    }
    // Reduce distance with right
    if(pos+1 < ssize_t(sets.size())){
        const std::set<coord_t, comp> &right = sets.at(pos+1);
        coord_t south(p.getLat()-dist, p.getLon());
        coord_t north(p.getLat()+dist, p.getLon());
        auto south_it = right.lower_bound(south);
        auto north_it = right.upper_bound(north);
        for(auto it = south_it; it != north_it; ++it){
            deg_t dist_ = coord_t::getDistanceDeg(p, *it);
            if(dist_ < dist){
                ret = *it;
                dist = dist_;
            }
        }
    }
    // Return
    return ret;
}
