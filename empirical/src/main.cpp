#include "GraphGenerator.h"
#include "DFS.h"
#include "KosarajuV.h"
#include "Astar.h"
#include "ShortestPath.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

typedef std::chrono::high_resolution_clock hrc;


int main(){
    std::ofstream ofs("../results.csv");
    if (!ofs.is_open()) throw std::runtime_error("Could not create output file");

    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 15000, 20000, 25000, 30000, 50000, 70000, 90000, 100000};
    std::vector<GraphGenerator> generators;
    for (int i : sizes) generators.push_back(GraphGenerator(i));
    std::cout << "Populating Graps...\n";

    for (auto g : generators) g.run();
    std::cout << "Populated!\n";

    std::cout << "Running Kosaraju on graphs...\n";
    std::vector<std::pair<int, long long>> kosarajuTimes;
    for (size_t i = 0 ; i < sizes.size() ; ++i) {
        DFS r;
        std::cout << generators.at(i).getDWGraph()->getNodes().size() << std::endl;
        DUGraph g = DUGraph(*generators.at(i).getDWGraph());
        auto start_time = hrc::now();
        KosarajuV k(&r);
        k.initialize(&g, 1);
        k.run();
        auto finish_time = hrc::now();
        long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
        kosarajuTimes.push_back(std::make_pair(sizes.at(i), execution_time));
    }
    std::cout << "Outputing to file\n";
    ofs << "Kosaraju\n";
    for (std::pair<int, long long> pair : kosarajuTimes) ofs << pair.first << "," << pair.second << ",\n";


    std::cout << "Running A* on graphs...\n";
    std::vector<std::pair<int, long long>> astarTimes;
    for (size_t i = 0 ; i < sizes.size() ; ++i) {
        //ShortestPath *shortestPath = new Astar();
        //shortestPath->initialize(&generators.at(i).getDWGraph(), 1, 6); <- Pick u and v
        //shortestPath->run();
        //astarTimes.push_back(std::make_pair(sizes.at(i),shortestPath->getStatistics().execution_time));
    }
    std::cout << "Outputing to file\n";
    std::cout << "A*\n";
    for (std::pair<int, long long> pair : astarTimes) ofs << pair.first << "," << pair.second << ",\n";

    ofs.close();
    return 0;
}