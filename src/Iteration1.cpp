#include "Iteration1.h"

Iteration1::Iteration1(){}

void Iteration1::initialize(const MapGraph *M_, const std::string &vans_path_, const std::string &clients_path_, const std::string &rides_path_){
    this->M            = M_;
    this->vans_path    = vans_path_;
    this->clients_path = clients_path_;
    this->rides_path   = rides_path_;
}

void Iteration1::run(){

}
