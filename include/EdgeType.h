#ifndef EDGETYPE_H_INCLUDED
#define EDGETYPE_H_INCLUDED

enum edge_type_t : char{
    NO          = 'n',
    MOTORWAY    = 'M',
    TRUNK       = 'T',
    PRIMARY     = 'P',
    SECONDARY   = 'S',
    TERTIARY    = 't',
    ROAD        = 'r',
    RESIDENTIAL = 'e',
    SLOW        = 's'
};

#endif //EDGETYPE_H_INCLUDED
