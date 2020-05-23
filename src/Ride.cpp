#include "Ride.h"

Ride::Event::Event(){}

Ride::Ride(){}

void Ride::setVan(Van v_){
    this->v = v_;
}

void Ride::addClient(Client c){
    C.push_back(c);
}

const std::vector<Client>& Ride::getClients() const{
    return C;
}

std::istream& operator>> (std::istream& is, Ride& r){
        is >> r.v;
        
        std::vector<Client> clients;
        size_t numClients; is >> numClients;
        for (size_t i = 0 ; i < numClients ; ++i){
            Client c;
            is >> c;
            clients.push_back(c);
        }
        r.C = clients;

        std::vector<Ride::Event> events;
        size_t numEvents; is >> numEvents;
        for (size_t i = 0 ; i < numEvents ; ++i){
            Ride::Event e;
            is >> e;
            events.push_back(e);
        }
        r.e = events;

        return is;
    }

std::ostream& operator<< (std::ostream& os, Ride& r){
	os << r.v << std::endl;
    os << r.C.size() << std::endl;
    for (size_t i = 0 ; i < r.C.size() ; ++i) os << r.C.at(i) << std::endl;
    os << r.e.size() << std::endl;
    for (size_t i = 0 ; i < r.e.size() ; ++i) os << r.e.at(i) << std::endl;
    return os;
}