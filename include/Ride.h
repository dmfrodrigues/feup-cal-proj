#ifndef RIDE_H_INCLUDED
#define RIDE_H_INCLUDED

#include "Van.h"
#include "Client.h"

#include <vector>

class Ride{
private:
    class Event{
    private:
        long long int time;
        event_type a;
        long long c;
    public:
        enum event_type:short{ cu = -1, cv = 0, c = 1};
    };

    Van v;
    std::vector<Client> C;
    std::vector<Event> e;

    friend std::istream& operator>> (std::istream& is, Ride& c);

    friend std::ostream& operator<< (std::ostream& os, Ride& c);
};


#endif //RIDE_H_INCLUDED
