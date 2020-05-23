#ifndef VAN_H_INCLUDED
#define VAN_H_INCLUDED

#include <vector>
#include <iostream>

class Van {
private:
	int capacity;
    std::string license;

public:

	int getCapacity();

    //std::vector<Van> getVansFromFile(std::string filename);

    bool operator<(const Van &v) const;

    friend std::istream& operator>> (std::istream& is, Van& v);

    friend std::ostream& operator<< (std::ostream& os, Van& v);
};


#endif //VAN_H_INCLUDED