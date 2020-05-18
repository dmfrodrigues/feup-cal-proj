#ifndef INTERESTING_NODE_H_INCLUDED
#define INTERESTING_NODE_H_INCLUDED

#include <iostream>

#include "DUGraph.h"

class InterestingNode {
private:
    std::string name;
    DUGraph::node_t node;

public:

    friend std::istream& operator>> (std::istream& is, InterestingNode& n){
        is >> n.name >> n.node;
        return is;
    }

    friend std::ostream& operator<< (std::ostream& os, InterestingNode& n){
        os << n.name << n.node;
        return os;
    } 

};

#endif //INTERESTING_NODE_H_INCLUDED