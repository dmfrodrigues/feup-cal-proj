#include "point.h"

point_t::point_t(){}

void point_t::setName(const encoded_string &s){
    name = s;
}

void point_t::setCoord(const coord_t &c){
    coord = c;
}

encoded_string point_t::getName() const {
    return name;
}

coord_t point_t::getCoord() const {
    return coord;
}

std::istream& operator>> (std::istream& is, point_t& n){
    is >> n.coord >> n.name;
    return is;
}

std::ostream& operator<< (std::ostream& os, const point_t& n){
    os << n.coord << " " << n.name;
    return os;
}
