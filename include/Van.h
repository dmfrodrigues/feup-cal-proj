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

    friend std::istream& operator>> (std::istream& is, Van& v){
        is >> v.license >> v.capacity;
        return is;
    }

    friend std::ostream& operator<< (std::ostream& os, Van& v){
        os << v.license << v.capacity;
        return os;
    } 
};


#endif //VAN_H_INCLUDED