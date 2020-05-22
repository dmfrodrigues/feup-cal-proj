#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"

#include <vector>

class Ride{
private:
    class Event{
    public:
        enum event_type:short{ cu = -1, cv = 0, c = 1};
    private:
        long long int time;
        event_type a;
        long long c;
    
    };

    Van v;
    std::vector<Client> C;
    std::vector<Event> e;

    friend std::istream& operator>> (std::istream& is, Ride& c);

    friend std::ostream& operator<< (std::ostream& os, Ride& c);
};


#endif //RIDE_H_INCLUDED
