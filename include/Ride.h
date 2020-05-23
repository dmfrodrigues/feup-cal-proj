#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"

#include <vector>
#include <iostream>

class Ride {
private:
    class Event{
    public:
        Event();
        enum class event_type:short{ ecu = -1, ecv = 0, ec = 1};
        friend std::istream& operator>> (std::istream& is, event_type& e){
            short x; is >> x;
            switch(x){
                case -1:
                    e= event_type::ecu;
                    break;
                case 0:
                    e = event_type::ecv;
                    break;
                case 1:
                    e = event_type::ec;
                    break;
                default:
                    return is;
            }    
            return is;
        }
        friend std::ostream& operator<< (std::ostream& os, event_type& e){
            switch(e){
                case event_type::ecu:
                    os << -1;
                    break;
                case event_type::ecv:
                   os << 0;
                    break;
                case event_type::ec:
                    os << 1;
                    break;
                default:
                    return os;
            }  
            return os;
        }

        friend std::istream& operator>> (std::istream& is, Event& e){
            is >> e.t >> e.a >> e.c;
            return is;
        }
        friend std::ostream& operator<< (std::ostream& os, Event& e){
            os << e.t << e.a << e.c;
            return os;
        }
    private:
        long long int t;
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

    friend std::istream& operator>> (std::istream& is, Ride& r);

    friend std::ostream& operator<< (std::ostream& os, Ride& r);
};


#endif //RIDE_H_INCLUDED
