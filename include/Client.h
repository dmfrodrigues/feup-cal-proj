#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "coord.h"

#include <string>
#include <vector>
#include <iostream>

class Client {
private:
	std::string clientName;
	int NIF;
	int numPeople;

	coord_t dest;
	long long int arrival;

	bool direction;

public:
    Client();
    Client(std::string clientName, int NIF, int numPeople, coord_t dest, long long int arrival, bool direction);
    
	std::string getClientName() const;
	int getNIF() const;
	int getNumPeople() const;
	coord_t getDest() const;
	long long int getArrival() const;
    bool getDirection() const;

    //std::vector<Client> getClientsFromFile(std::string filename);

    friend std::istream& operator>> (std::istream& is, Client& c){
        is >> c.clientName >> c.NIF >> c.dest >> c.arrival >> c.direction;
        return is;
    }

    friend std::ostream& operator<< (std::ostream& os, Client& c){
        os << c.clientName << " " << c.NIF << " " << c.numPeople << " " << c.dest << " " << c.arrival << " " << c.direction;
        return os;
    }
};

#endif //CLIENT_H_INCLUDED