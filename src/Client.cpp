#include "Client.h"

#include <fstream>
#include <iomanip>

Client::Client(){}

Client::Client(std::string clientName_, int NIF_, coord_t dest_, long long int arrival_, bool direction_){
	this->clientName = clientName_;
	this->NIF = NIF_;
	this->dest = dest_;
	this->arrival = arrival_;
	this->direction = direction_;
}

std::string Client::getClientName() const {
	return clientName;
}

int Client::getNIF() const {
	return NIF;
}

coord_t Client::getDest() const {
	return dest;
}

DWGraph::weight_t Client::getArrival() const {
	return arrival;
}

bool Client::getDirection() const {
    return direction;
}

bool Client::operator<(const Client &c) const{
	return (arrival < c.arrival);
}

std::istream& operator>> (std::istream& is, Client& c){
	is >> c.clientName >> c.NIF >> c.dest >> c.arrival >> c.direction;
	return is;
}

std::ostream& operator<< (std::ostream& os, const Client& c){
	os << std::left << std::setw(16) << c.clientName << "\t" << c.NIF << "\t" << c.dest << "\t" << c.arrival << "\t" << c.direction;
	return os;
}
