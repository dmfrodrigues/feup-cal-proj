#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

struct statistics_t {
    size_t analysed_nodes;
    size_t analysed_edges;
    /**
     * @brief Execution time of an algorithm, in integer microseconds.
     */
    long long execution_time;
};

#endif //STATISTICS_H_INCLUDED
