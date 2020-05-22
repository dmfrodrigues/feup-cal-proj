#include "Client.h"

#include <fstream>

Client::Client(std::string clientName, int NIF, int numPeople, coord_t dest, long long int arrival, bool direction){
	this->clientName = clientName;
	this->NIF = NIF;
	this->numPeople = numPeople;
	this->dest = dest;
	this->arrival = arrival;
	this->direction = direction;
}

std::string Client::getClientName() const {
	return clientName;
}

int Client::getNIF() const {
	return NIF;
}

int Client::getNumPeople() const {
	return numPeople;
}

coord_t Client::getDest() const {
	return dest;
}

long long int Client::getArrival() const {
	return arrival;
}

bool Client::getDirection() const {
    return direction;
}

// std::vector<Client> Client::getClientsFromFile(std::string filename){
//  std::vector<Client> result;
    
//  std::ifstream ifs("resources/" + filename);
// 	if(!ifs.is_open()) throw std::runtime_error("Could not open clients requests file");

// 	std::string name;
// 	int nif, npersons;
//  DUGraph::node_t node;
//  long long int t; 
// 	while(!ifs.eof()) {
// 		Client c;
//      ifs >> c;
// 		result.push_back(c);
// 	}
// 	return result;
// }

std::istream& operator>> (std::istream& is, Client& c){
        is >> c.clientName >> c.NIF >> c.dest >> c.arrival >> c.direction;
        return is;
    }

std::ostream& operator<< (std::ostream& os, Client& c){
	os << c.clientName << " " << c.NIF << " " << c.numPeople << " " << c.dest << " " << c.arrival << " " << c.direction;
	return os;
}