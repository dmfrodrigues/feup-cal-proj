#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

#include <iostream>

/**
 * @brief Coordinates
 * 
 */
class coord_t {
public:
    typedef double deg_t;
private:
    double lat = 0, lon = 0;
    double getMetersPerLatDeg() const;
    double getMetersPerLonDeg() const;
public:
    /**
     * @brief Construct without arguments
     * 
     */
    coord_t();

    /**
     * @brief Construct from latitude and longitude
     * 
     * @param lat Latitude
     * @param lon Longitude
     */
    coord_t(deg_t lat, deg_t lon);

    /**
     * @brief Get distance between two positions in SI units (meters).
     * 
     * @param p1        First position
     * @param p2        Second position
     * @return double   Distance between them in meters
     */
    static double getDistanceSI(const coord_t &p1, const coord_t &p2);

    /**
     * @brief Get distance between two positions in degrees.
     * 
     * @param p1        First position
     * @param p2        Second position
     * @return deg_t    Distance between them in degrees
     */
    static deg_t getDistanceDeg(const coord_t &p1, const coord_t &p2);

    coord_t operator+(const coord_t &p) const;
    coord_t operator/(double d) const;
    bool operator==(const coord_t &c) const;
    bool operator< (const coord_t &c) const;
    deg_t getLat() const;
    deg_t getLon() const;
    friend std::istream& operator>>(std::istream &is,       coord_t &c);
    friend std::ostream& operator<<(std::ostream &os, const coord_t &c);
};

#endif //COORD_H_INCLUDED
