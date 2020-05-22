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
        enum event_type:short{ cu = -1, cv = 0, c = 1};
        friend std::istream& operator>> (std::istream& is, Event& e){
            is >> e.time >> e.a >> e.c;
            return is;
        }
        friend std::ostream& operator<< (std::ostream& os, Event& e){
            os << e.time << " " << e.a << " " << e.c;
            return os;
        }
    private:
        long long int time;
        event_type a;
        long long c;
    
    };

    Van v;
    std::vector<Client> C;
    std::vector<Event> e;

public:
    Ride();
};


#endif //RIDE_H_INCLUDED
