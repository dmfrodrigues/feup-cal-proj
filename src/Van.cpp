#include "Van.h"


unsigned Van::getCapacity() {
	return capacity;
}

bool Van::operator<(const Van &v) const{
    return (license < v.license);
}

std::istream& operator>> (std::istream& is, Van& v){
        is >> v.license >> v.capacity;
        return is;
    }

std::ostream& operator<< (std::ostream& os, const Van& v){
	os << v.license << " " << v.capacity;
	return os;
} 
