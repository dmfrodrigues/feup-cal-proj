#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "Client.h"
#include "point.h"

#include <stdexcept> 
#include <vector>
#include <fstream>

using namespace std;

#define HOURS_TO_MICROS ((long long)(60)*60*1000000)
#define MIN_TO_MICROS ((long long)(60)*1000000)

class Generator{
private:
    string points_relative_path;
    string output_path;
    int n_res;
    long long start_time;
    long long end_time;
    bool only_trainstation;

public:
    Generator(string points_relative_path, string output_path, int n_res, long long start_time, long long end_time, bool only_trainstation);
    void run();
};

#endif //GENERATOR_H_INCLUDED