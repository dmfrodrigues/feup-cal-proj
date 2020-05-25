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
        /**
         * @brief Construct a new Event object
         * 
         */
        Event();
        /**
         * @brief Construct a new Event object
         * 
         * @param t time point of event
         * @param a event type(this constructor only accepts a = BE_THERE)
         * @param c client object
         */
        Event(DWGraph::weight_t t, event_type a, Client c);
        /**
         * @brief Construct a new Event object
         * 
         * @param t time point of event
         * @param a event type(this constructor only accepts a != BE_THERE)
         * @param u destination node
         */
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
    /**
     * @brief Construct a new Ride object
     * 
     */
    Ride();
    
    void setVan(Van v);

    void addClient(Client c);

    const std::vector<Client>& getClients() const;

    /**
     * @brief Clear ride events and mark the leaving of the station
     * 
     * @param station node
     * @param t time point of event
     */
    void leaveStation(DWGraph::node_t station, DWGraph::weight_t t);
    /**
     * @brief Mark arrival at the station
     * 
     * @param station node
     * @param t time point of event
     */
    void arriveStation(DWGraph::node_t station, DWGraph::weight_t t);

    /**
     * @brief Mark the dropping off of a Client
     * 
     * @param c client
     * @param t time point of event
     */
    void dropClient(Client c, DWGraph::weight_t t);

    friend std::istream& operator>> (std::istream& is, Ride& r);

    friend std::ostream& operator<< (std::ostream& os, const Ride& r);
};

#endif //RIDE_H_INCLUDED
