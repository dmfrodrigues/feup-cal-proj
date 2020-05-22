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
        enum event_type:short{ ecu = -1, ecv = 0, ec = 1};
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
