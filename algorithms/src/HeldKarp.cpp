#include "HeldKarp.h"

HeldKarp::HeldKarp(){}

void HeldKarp::initialize(const DWGraph::DWGraph *G_, DWGraph::node_t s_){
    this->G = G_;
    this->s = s_;
}

void HeldKarp::run(){

}

std::list<DWGraph::node_t> HeldKarp::getTour() const{
    return path;
}

statistics_t HeldKarp::getStatistics() const{
    return stats;
}
