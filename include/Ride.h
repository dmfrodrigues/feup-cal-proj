#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"
#include "DWGraph.h"

#include <vector>
#include <iostream>

class Ride {
private:
    class Event{
    public:
        enum event_type:short{
            DROP_CLIENT = -1,
            BE_THERE = 0,
            GET_CLIENT = 1
        };
        Event(DWGraph::weight_t t, event_type a, long long c);
        friend std::istream& operator>> (std::istream& is, event_type& e){
            short x; is >> x;
            e = static_cast<event_type>(x);
            return is;
        }
        friend std::ostream& operator<< (std::ostream& os, const event_type& e){
            os << e;
            return os;
        }

        friend std::istream& operator>> (std::istream& is, Event& e){
            is >> e.t >> e.a >> e.c;
            return is;
        }
        friend std::ostream& operator<< (std::ostream& os, const Event& e){
            os << e.t << e.a << e.c;
            return os;
        }
    private:
        DWGraph::weight_t t;
        event_type a;
        long long c;
    };

    Van v;
    std::vector<Client> C;
    std::vector<Event> e;

public:
    Ride();

    void setVan(Van v);

    void addClient(Client c);

    const std::vector<Client>& getClients() const;

    void leaveStation(DWGraph::node_t station, DWGraph::weight_t t);

    void dropClient(Client c, weight_t t);

    friend std::istream& operator>> (std::istream& is, Ride& r);

    friend std::ostream& operator<< (std::ostream& os, const Ride& r);
};


#endif //RIDE_H_INCLUDED
