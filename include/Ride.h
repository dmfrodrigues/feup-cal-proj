#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"
#include "DWGraph.h"

#include <vector>
#include <iostream>

/**
 * @brief Ride class
 * 
 */
class Ride {
public:
    /**
     * @brief Event class
     * 
     */
    class Event{
    public:
        /**
         * @brief event_type enum
         * 
         */
        enum event_type:short{
            DROP_CLIENT = -1,
            BE_THERE = 0,
            GET_CLIENT = 1
        };
        Event();
        Event(DWGraph::weight_t t, event_type a, Client c);
        Event(DWGraph::weight_t t, event_type a, DWGraph::node_t u);

        DWGraph::weight_t getTime() const;
        event_type getType() const;
        const Client& getClient() const;
        DWGraph::node_t getNode() const;

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

    /**
     * @brief Clear ride events and mark the leaving of the station
     * 
     * @param station node
     * @param t duration of the event
     */
    void leaveStation(DWGraph::node_t station, DWGraph::weight_t t);
    /**
     * @brief Mark arrival at the station
     * 
     * @param station node
     * @param t duration of the event
     */
    void arriveStation(DWGraph::node_t station, DWGraph::weight_t t);

    /**
     * @brief Mark the dropping off of a Client
     * 
     * @param c client
     * @param t duration of the event
     */
    void dropClient(Client c, DWGraph::weight_t t);

    DWGraph::weight_t getStartTime() const;
    DWGraph::weight_t getEndTime  () const;

    const std::vector<Event>& getEvents() const;

    friend std::istream& operator>> (std::istream& is, Ride& r);

    friend std::ostream& operator<< (std::ostream& os, const Ride& r);
};

#endif //RIDE_H_INCLUDED
