#ifndef VAN_H_INCLUDED
#define VAN_H_INCLUDED

#include <vector>
#include <iostream>

/**
 * @brief Van class
 * 
 */
class Van {
private:
	unsigned capacity;
    std::string license;

public:

	unsigned getCapacity();

    bool operator<(const Van &v) const;

    friend std::istream& operator>> (std::istream& is, Van& v);

    friend std::ostream& operator<< (std::ostream& os, const Van& v);
};


#endif //VAN_H_INCLUDED