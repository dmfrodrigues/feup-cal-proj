#include "Van.h"


int Van::getCapacity() {
	return capacity;
}

// std::vector<Van> Client::getVansFromFile(std::string filename){
//  std::vector<Van> result;
    
//  std::ifstream ifs("resources/" + filename);
// 	if(!ifs.is_open()) throw std::runtime_error("Could not open vans file");

// 	std::string license;
// 	int capacity;
// 	while(!ifs.eof()) {
// 		Van v;
//      ifs >> v;
// 		result.push_back(v);
// 	}
// 	return result;
// }

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
