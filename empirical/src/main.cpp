#include "GraphGenerator.h"
#include "DFS.h"
#include "KosarajuV.h"
#include "Astar.h"
#include "Dijkstra.h"
#include "ShortestPath.h"
#include "ShortestPathAll.h"
#include "HeldKarp.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

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
    DWGraph::weight_t operator()(const std::unordered_set<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
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

    std::cout << "Running Kosaraju on graphs...\n";
    std::vector<std::pair<int, long long>> kosarajuTimes;
    for (size_t i = 0 ; i < sizes.size() ; ++i) {
        std::cout << i << std::endl;
        DFS r;
        DUGraph g = DUGraph(*generators.at(i).getDWGraph());
        KosarajuV k(&r);

        long long time = 0;
        for(int n = 0; n < NRUNS; ++n){
            auto start_time = hrc::now();
            k.initialize(&g, 1);
            k.run();    
            auto finish_time = hrc::now();
            time += std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
        }

        kosarajuTimes.push_back(std::make_pair(sizes.at(i), time/NRUNS));
    }
    std::cout << "Outputing to file\n";
    ofs << "Kosaraju\n";
    for (std::pair<int, long long> pair : kosarajuTimes) ofs << pair.first << "," << pair.second << ",\n";
    

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

    {
        std::cout << "Running Held-Karp" << std::endl;
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
            tsp->initialize(&nodes, source_node, &w);
            try{
                tsp->run();
            } catch(const std::exception &e){
                std::cerr << "Caught exception" << std::endl;
                throw e;
            }

            heldKarpTimes.push_back(std::make_pair(sizes[i], tsp->getStatistics().execution_time));
            delete tsp;
        }
        std::cout << "Outputing to file\n";
        ofs << "Held-Karp\n";
        for (std::pair<int, long long> pair : heldKarpTimes) ofs << pair.first << "," << pair.second << ",\n";
    }

    ofs.close();
    return 0;
}