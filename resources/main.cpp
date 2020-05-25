#include "input_generator.h"

int main(int argc, char *argv[]){   

    if(argc < 2) throw invalid_argument("at least one argument must be provided");

    if (argc != 5 && argc != 6) {
        cout << "Usage: ./generator OUTPUT_FILE NUMBER_CLIENTS TIME_START TIME_END\n";
        return 1;
    }

    string path = argv[1];
    int n_res = atoi(argv[2]);
    long long start_time = atof(argv[3])*HOURS_TO_MICROS;
    long long end_time   = atof(argv[4])*HOURS_TO_MICROS;
    bool only_trainstation = (argc == 6 && string(argv[5]) == "-t");

    InputGenerator g("../map/processed/AMP.points", path, n_res, start_time, end_time, only_trainstation);
    g.run();
    return 0;
}