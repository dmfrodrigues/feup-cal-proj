#include "Ride.h"

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

Ride::Event::Event(DWGraph::weight_t t_, Ride::Event::event_type a_, long long c_){
    t = t_;
    a = a_;
    c = c_;
}

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

void Ride::leaveStation(node_t station, weight_t t){
    e.clear();
    e.push_back(Event(t, Event::event_type::BE_THERE, station));
}

void Ride::dropClient(Client c, weight_t t){
    e.push_back(Event(t, Event::event_type::DROP_CLIENT, c));
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

std::ostream& operator<< (std::ostream& os, const Ride& r){
	os << r.v;
    os << "\n" << r.C.size();
    for (size_t i = 0 ; i < r.C.size() ; ++i) os << "\n" << r.C.at(i);
    os << r.e.size() << std::endl;
    for (size_t i = 0 ; i < r.e.size() ; ++i) os << "\n" << r.e.at(i);
    return os;
}