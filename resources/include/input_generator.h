#ifndef INPUT_GENERATOR_H_INCLUDED
#define INPUT_GENERATOR_H_INCLUDED

#include "Client.h"
#include "point.h"

#include <stdexcept> 
#include <vector>
#include <fstream>

using namespace std;

#define HOURS_TO_MICROS ((long long)(60)*60*1000000)
#define MIN_TO_MICROS ((long long)(60)*1000000)

class InputGenerator{
private:
    string points_relative_path;
    string output_path;
    int n_res;
    long long start_time;
    long long end_time;
    bool only_trainstation;
    std::list<Client> clients;

public:
    InputGenerator(string points_relative_path, string output_path, int n_res, long long start_time, long long end_time, bool only_trainstation);
    void run();
    string getOutputPath() const;
};

#endif //INPUT_GENERATOR_H_INCLUDED