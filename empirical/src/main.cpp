#include "GraphGenerator.h"
#include "DFS.h"
#include "KosarajuV.h"
#include "Astar.h"
#include "Dijkstra.h"
#include "ShortestPath.h"
#include "ShortestPathAll.h"
#include "HeldKarp.h"
#include "input_generator.h"
#include "Iteration1.h"
#include "Iteration2.h"
#include "MapGraph.h"
#include "VStripes.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <sstream>

#define NRUNS 5

typedef DWGraph::weight_t weight_t;
typedef DWGraph::node_t node_t;
typedef std::vector<weight_t> VI;
typedef std::vector<VI> VVI;
typedef std::chrono::high_resolution_clock hrc;

class weight_matrix : public TravellingSalesman::weight_function {
private:
    const VVI &M;
public:
    weight_matrix(const VVI &M_):M(M_){}
    DWGraph::weight_t operator()(const std::unordered_multiset<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
        return M.at(u).at(v);
    }
};

int main(){
    std::ofstream ofs("../results.csv");
    if (!ofs.is_open()) throw std::runtime_error("Could not create output file");

    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 15000, 20000, 25000, 30000, 50000, 70000, 90000, 100000};
    std::vector<GraphGenerator> generators;
    for (int i : sizes) generators.push_back(GraphGenerator(i));
    std::cout << "Populating Graps...\n";

    for (auto g : generators) g.run();
    std::cout << "Populated!\n";

    {
        std::cout << "Running Kosaraju on graphs...\n";
        std::vector<std::pair<int, long long>> kosarajuTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i) {
            std::cout << i << std::endl;
            DFS r;
            DUGraph g = DUGraph(*generators.at(i).getDWGraph());
            auto start_time = hrc::now();
            KosarajuV k(&r);
            for(int n = 0; n < NRUNS; ++n){
                k.initialize(&g, 1);
                k.run();
            }
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            kosarajuTimes.push_back(std::make_pair(sizes.at(i), execution_time/NRUNS));
        }
        std::cout << "Outputing to file\n";
        ofs << "Kosaraju\n";
        for (std::pair<int, long long> pair : kosarajuTimes) ofs << pair.first << "," << pair.second << ",\n";
    }
    

    // std::cout << "Running A* on graphs...\n";
    // std::vector<std::pair<int, long long>> astarTimes;
    // for (size_t i = 0 ; i < sizes.size() ; ++i) {
    //     ShortestPath *shortestPath = new Astar();
    //     shortestPath->initialize(generators.at(i).getDWGraph(), 1, 6); <- Pick u and v
    //     shortestPath->run();
    //     astarTimes.push_back(std::make_pair(sizes.at(i),shortestPath->getStatistics().execution_time));
    // }
    // std::cout << "Outputing to file\n";
    // std::cout << "A*\n";
    // for (std::pair<int, long long> pair : astarTimes) ofs << pair.first << "," << pair.second << ",\n";

    {
        std::cout << "Running Dijkstra\n";
        std::vector<std::pair<int, long long>> dijkstraTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << i << std::endl;
            ShortestPathOneMany *shortestPath = new Dijkstra();
            long long time = 0;
            for(int n = 0; n < NRUNS; ++n){
                shortestPath->initialize(generators.at(i).getDWGraph(), 1);
                shortestPath->run();
                time += shortestPath->getStatistics().execution_time;
            }
            dijkstraTimes.push_back(std::make_pair(sizes.at(i),time/NRUNS));
        }
        std::cout << "Outputing to file\n";
        ofs << "Dijkstra\n";
        for (std::pair<int, long long> pair : dijkstraTimes) ofs << pair.first << "," << pair.second << ",\n";
    }

    {
        std::cout << "Running Held-Karp\n";
        std::vector<size_t> sizes({2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        std::vector<std::pair<int, long long>> heldKarpTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << i << std::endl;
            const size_t &sz = sizes[i];
            std::list<node_t> nodes;{
                for(node_t u = 0; u < node_t(sz); ++u)
                    nodes.push_back(u);
            }
            const node_t source_node = 0;
            VVI M(sz, VI(sz, 0));{
                for(size_t i = 0; i < sz; ++i){
                    for(size_t j = 0; j < sz; ++j){
                        if(i == j) continue;
                        M[i][j] = rand()%10000 + 1;
                    }
                }
            }
            weight_matrix w(M);

            TravellingSalesman *tsp = new HeldKarp();
            long long time = 0;
            for(int n = 0; n < NRUNS; ++n){
                tsp->initialize(&nodes, source_node, &w);
                try{
                    tsp->run();
                } catch(const std::exception &e){
                    std::cerr << "Caught exception" << std::endl;
                    throw e;
                }
                time += tsp->getStatistics().execution_time;
            }
            heldKarpTimes.push_back(std::make_pair(sizes[i], time/NRUNS));
            delete tsp;
        }
        std::cout << "Outputing to file\n";
        ofs << "Held-Karp\n";
        for (std::pair<int, long long> pair : heldKarpTimes) ofs << pair.first << "," << pair.second << ",\n";
    }

/*
    MapGraph M("../map/processed/AMP");

    {
        std::cout << "Running 1st Iteration analysis\n";
        std::vector<int> sizes = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
        std::vector<InputGenerator> inputs;
        std::vector<std::pair<int, long long>> firstIterationTimes;
        for (int i : sizes) {
            std::ostringstream oss; oss << "txts/c" << i << ".clients";
            std::string c = oss.str();
            std::cout << c << std::endl;
            inputs.push_back(InputGenerator("../map/processed/AMP.points", c, i, rand() % 4 + 9, rand() % 4 + 19, true));
        }
        for (InputGenerator ig : inputs) ig.run();
        std::cout << "Generated clients ; running...\n";
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << sizes.at(i) << std::endl;
            auto start_time = hrc::now();
            Iteration1 it;
            it.initialize(&M, "../resources/it1_01.vans", inputs.at(i).getOutputPath(), "txts/r.rides");
            it.run();
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            firstIterationTimes.push_back(std::make_pair(sizes.at(i), execution_time));
            std::string c = inputs.at(i).getOutputPath();
            remove(c.c_str());
        }
        std::cout << "Outputing to file\n";
        ofs << "1st Iteration\n";
        for (std::pair<int, long long> pair : firstIterationTimes) ofs << pair.first << "," << pair.second << ",\n";
        remove("txts/r.rides");
    }

    {
        std::cout << "Running 2nd Iteration analysis\n";
        std::vector<int> sizes = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
        std::vector<InputGenerator> inputs;
        std::vector<std::pair<int, long long>> secondIterationTimes;
        for (int i : sizes) {
            std::ostringstream oss; oss << "txts/c" << i << ".clients";
            std::string c = oss.str();
            std::cout << c << std::endl;
            inputs.push_back(InputGenerator("../map/processed/AMP.points", c, i, rand() % 4 + 9, rand() % 4 + 19, true));
        }
        for (InputGenerator ig : inputs) ig.run();
        std::cout << "Generated clients ; running...\n";
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << sizes.at(i) << std::endl;
            auto start_time = hrc::now();
            Iteration2 it;
            it.initialize(&M, "../resources/it2_01.vans", inputs.at(i).getOutputPath(), "txts/r.rides");
            it.run();
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            secondIterationTimes.push_back(std::make_pair(sizes.at(i), execution_time));
            std::string c = inputs.at(i).getOutputPath();
            remove(c.c_str());
        }
        std::cout << "Outputing to file\n";
        ofs << "2nd Iteration\n";
        for (std::pair<int, long long> pair : secondIterationTimes) ofs << pair.first << "," << pair.second << ",\n";
        remove("txts/r.rides");
    }
*/
    {
        std::cout << "Running VStripes analysis (Varying nodes)\n";
        std::cout << "Generating grids...\n";
        std::vector<std::list<coord_t>> grids;
        std::vector<int> sizes = {5, 10, 50, 100, 250, 500, 750, 1000};
        for (int size : sizes){
            std::list<coord_t> x;
            for(size_t i = 0 ; i < size ; ++i)
                for (size_t j = 0 ; j < size ; ++j)
                    x.push_back(coord_t(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/41.3112)) + 41.0055 , static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/8.4925)) + 8.7523 - 10));
            grids.push_back(x);
        }
        std::cout << "Running node analysis\n";

        std::vector<std::pair<int, long long>> VStripesNodesIterationTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << sizes.at(i) << std::endl;
            VStripes vs(0.025);
            auto start_time = hrc::now();
            for(int n = 0; n < NRUNS; ++n){
                vs.initialize(grids.at(i));
                vs.run();
            }
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            VStripesNodesIterationTimes.push_back(std::make_pair(sizes.at(i)*sizes.at(i), execution_time/NRUNS));
        }
        std::cout << "Outputing to file\n";
        ofs << "VStripes Node varying Iteration\n";
        for (std::pair<int, long long> pair : VStripesNodesIterationTimes) ofs << pair.first << "," << pair.second << ",\n";


        std::cout << "Running delta analysis\n";

        std::list<coord_t> grid = grids.at(6);
        std::vector<coord_t::deg_t> deltas = {0.001, 0.005, 0.01, 0.025, 0.05, 0.1, 0.2, 0.25};
        std::vector<std::pair<double, long long>> vStripesDeltasIterationTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << deltas.at(i) << std::endl;
            VStripes vs(deltas.at(i));
            auto start_time = hrc::now();
            for(int n = 0; n < NRUNS; ++n){
                vs.initialize(grid);
                vs.run();
            }
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            vStripesDeltasIterationTimes.push_back(std::make_pair(deltas.at(i), execution_time/NRUNS));
        }
        std::cout << "Outputing to file\n";
        ofs << "VStripes Delta varying Iteration\n";
        for (std::pair<double, long long> pair : vStripesDeltasIterationTimes) ofs << pair.first << "," << pair.second << ",\n";
    }

    ofs.close();
    return 0;
}