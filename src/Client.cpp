#include "Client.h"

#include <fstream>

std::string Client::getClientName() const {
	return clientName;
}

int Client::getNIF() const {
	return NIF;
}

int Client::getNumPeople() const {
	return numPeople;
}

DUGraph::node_t Client::getDest() const {
	return dest;
}

long long int Client::getArrival() const {
	return arrival;
}

bool Client::getDirection() const {
    return direction;
}

std::vector<Client> Client::getClientsFromFile(std::string filename){
    std::vector<Client> result;
    
    std::ifstream ifs("resources/" + filename);
	if(!ifs.is_open()) return result;

	int N;
	ifs >> N;

	std::string name;
	int nif, npersons;
    DUGraph::node_t node;
    long long int t; 
	for (size_t i = 0 ; i < N; i++) {
		Client c;
        ifs >> c;
		result.push_back(c);
	}
	return result;
}