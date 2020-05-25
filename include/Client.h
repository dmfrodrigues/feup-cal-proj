#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "coord.h"
#include "DWGraph.h"

#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Client data
 * 
 */
class Client {
private:
	std::string clientName;
	int NIF;

	coord_t dest;
	DWGraph::weight_t arrival;

	bool direction;

public:
	/**
	 * @brief Construct without arguments
	 * 
	 */
    Client();

	/**
	 * @brief Construct from name, nif, destination, arrival, direction relative to the station
	 * 
	 * @param clientName 
	 * @param NIF 
	 * @param dest 
	 * @param arrival 
	 * @param direction 
	 */
    Client(std::string clientName, int NIF, coord_t dest, long long int arrival, bool direction);
    
	std::string getClientName() const;
	int getNIF() const;
	coord_t getDest() const;
	DWGraph::weight_t getArrival() const;
    bool getDirection() const;

	bool operator<(const Client &c) const;

    friend std::istream& operator>> (std::istream& is, Client& c);
    friend std::ostream& operator<< (std::ostream& os, const Client& c);
};

#endif //CLIENT_H_INCLUDED