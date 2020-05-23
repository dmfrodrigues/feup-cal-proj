#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"
#include "DWGraph.h"

#include <vector>
#include <iostream>

class Ride {
public:
    class Event{
    public:
        enum event_type:short{
            DROP_CLIENT = -1,
            BE_THERE = 0,
            GET_CLIENT = 1
        };
        Event();
        Event(DWGraph::weight_t t, event_type a, Client c);
        Event(DWGraph::weight_t t, event_type a, DWGraph::node_t u);
        friend std::istream& operator>> (std::istream& is, event_type& e);
        friend std::ostream& operator<< (std::ostream& os, const event_type& e);

        friend std::istream& operator>> (std::istream& is, Event& e);
        friend std::ostream& operator<< (std::ostream& os, const Event& e);
    private:
        DWGraph::weight_t t;
        event_type a;
        Client c;
        DWGraph::node_t u;
    };
    
private:
    Van v;
    std::vector<Client> C;
    std::vector<Event> e;

public:
    Ride();

    void setVan(Van v);

    void addClient(Client c);

    const std::vector<Client>& getClients() const;

    void leaveStation(DWGraph::node_t station, DWGraph::weight_t t);
    void arriveStation(DWGraph::node_t station, DWGraph::weight_t t);

    void dropClient(Client c, DWGraph::weight_t t);

    friend std::istream& operator>> (std::istream& is, Ride& r);

    friend std::ostream& operator<< (std::ostream& os, const Ride& r);
};

#endif //RIDE_H_INCLUDED
