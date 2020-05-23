#include "Ride.h"

typedef DWGraph::node_t node_t;
typedef DWGraph::weight_t weight_t;

Ride::Event::Event(){}

Ride::Event::Event(DWGraph::weight_t t_, Event::event_type a_, Client c_){
    if (a_ == event_type::BE_THERE) throw std::invalid_argument("");
    this->t = t_;
    this ->a = a_;
    this->c = c_;
}

Ride::Event::Event(DWGraph::weight_t t_, Event::event_type a_, DWGraph::node_t u_){
    if (a_ != event_type::BE_THERE) throw std::invalid_argument("");
    this->t = t_;
    this ->a = a_;
    this->u = u_;
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

void Ride::arriveStation(node_t station, weight_t t){
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
    os << "\n" << r.e.size();
    for (size_t i = 0 ; i < r.e.size() ; ++i) os << "\n" << r.e.at(i);
    return os;
}

std::istream& operator>> (std::istream& is, Ride::Event::event_type& e){
    short x; is >> x;
    e = static_cast<Ride::Event::event_type>(x);
    return is;
}
std::ostream& operator<< (std::ostream& os, const Ride::Event::event_type& e){
    os << e;
    return os;
}

std::istream& operator>> (std::istream& is, Ride::Event& e){
    is >> e.t;
    short a;
    is >> a;
    e.a = static_cast<Ride::Event::event_type>(a);
    switch(e.a){
        case -1: is >> e.c; break;
        case  0: is >> e.u; break;
        case +1: is >> e.c; break;
        default:            break;
    }
    return is;
}
std::ostream& operator<< (std::ostream& os, const Ride::Event& e){
    os << e.t << " " << static_cast<short>(e.a) << " ";
    switch(e.a){
        case -1: os << e.c; break;
        case  0: os << e.u; break;
        case +1: os << e.c; break;
        default:            break;
    }
    return os;
}
