#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

struct coord_t {
    double lat, lon;
    /**
     * @brief Get distance between two positions in SI units (meters).
     * 
     * @param p1        First position
     * @param p2        Second position
     * @return double   Distance between them in meters
     */
    static double getDistanceSI(const coord_t &p1, const coord_t &p2);

    coord_t operator+(const coord_t &p) const;
    coord_t operator/(double d) const;
private:
    double getMetersPerLatDeg() const;
    double getMetersPerLonDeg() const;
};

#endif //COORD_H_INCLUDED
