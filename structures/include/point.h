#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include "coord.h"
#include "encoded_string.h"

#include "DUGraph.h"

/**
 * @brief Point of interest
 * 
 */
class point_t {
private:
    encoded_string name = "";
    coord_t coord = coord_t();
public:
    /**
     * @brief Construct without arguments
     * 
     */
    point_t();

    void setName(const encoded_string &s);
    void setCoord(const coord_t &c);

    encoded_string getName() const;
    coord_t getCoord() const;

    friend std::istream& operator>> (std::istream& is,       point_t& n);
    friend std::ostream& operator<< (std::ostream& os, const point_t& n);

};

#endif //POINT_H_INCLUDED