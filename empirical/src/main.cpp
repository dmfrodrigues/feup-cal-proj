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
#include <cmath>

#define NRUNS 20

typedef DWGraph::weight_t weight_t;
typedef DWGraph::node_t node_t;
typedef std::vector<weight_t> VI;
typedef std::vector<VI> VVI;
typedef std::chrono::high_resolution_clock hrc;

#define SECONDS_TO_MICROS       1000000     // Convert seconds to milliseconds
#define KMH_TO_MS               (1.0/3.6)   // Convert km/h to m/s

class weight_matrix : public TravellingSalesman::weight_function {
private:
    const VVI &M;
public:
    weight_matrix(const VVI &M_):M(M_){}
    DWGraph::weight_t operator()(const std::unordered_multiset<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
        return M.at(u).at(v);
    }
};

class MapGraph::DistanceHeuristic : public Astar::heuristic_t{
private:
    const std::unordered_map<node_t, coord_t> &nodes;
    coord_t dst_pos;
    double factor;
public:
    DistanceHeuristic(const std::unordered_map<node_t, coord_t> &nodes_,
                      coord_t dst_pos_,
                      double factor_): nodes(nodes_), dst_pos(dst_pos_), factor(factor_){}
    weight_t operator()(node_t u) const{
        auto d = coord_t::getDistanceSI(dst_pos, nodes.at(u));
        return weight_t(d*factor);
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
 /*   
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
    
    {
        std::cout << "Running Dijkstra\n";
        std::vector<std::pair<int, long long>> dijkstraTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << i << std::endl;
            ShortestPathOneMany *sp = new Dijkstra();
            long long time = 0;
            for(int n = 0; n < NRUNS; ++n){
                sp->initialize(generators.at(i).getDWGraph(), 1);
                sp->run();
                time += sp->getStatistics().execution_time;
            }
            dijkstraTimes.push_back(std::make_pair(sizes.at(i),time/NRUNS));
            delete sp;
        }
        std::cout << "Outputing to file\n";
        ofs << "Dijkstra\n";
        for (std::pair<int, long long> pair : dijkstraTimes) ofs << pair.first << "," << pair.second << ",\n";
    }

    {
        std::cout << "Running Held-Karp\n";
        std::vector<size_t> sizes({2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
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
    
    MapGraph M("../map/processed/AMP");

    {
        DWGraph::DWGraph graph = M.getConnectedGraph();
        std::unordered_map<DWGraph::node_t, coord_t> nodes = M.getNodes();
        const std::vector<node_t> connected_nodes(graph.getNodes().begin(), graph.getNodes().end());
        std::cout << "Running A*\n";
        int tries = 0;
        std::map<DWGraph::weight_t, long long> distancesAndTimes;
        std::map<DWGraph::weight_t, int> nValuesInserted;
        while(distancesAndTimes.size() < 500){
            std::cout << tries << "\n"; tries++;

            DWGraph::node_t srcN = connected_nodes[rand() % connected_nodes.size()];
            DWGraph::node_t dstN = connected_nodes[rand() % connected_nodes.size()];

            Astar::heuristic_t *w = new MapGraph::DistanceHeuristic(nodes, nodes.at(dstN), double(SECONDS_TO_MICROS)/(90.0*KMH_TO_MS));
            ShortestPath *sp = new Astar(w);
            sp->initialize(&graph, srcN, dstN);
            sp->run();
            DWGraph::weight_t dist = sp->getPathWeight(); if(dist == 0) continue;
            long long time = sp->getStatistics().execution_time;
            if (!nValuesInserted.insert(std::make_pair<DWGraph::weight_t&, int>(dist, 1)).second) nValuesInserted[dist]++;
            if (!distancesAndTimes.insert(std::make_pair<DWGraph::weight_t&, long long&>(dist, time)).second) distancesAndTimes[dist] += time;
        
            delete sp;
            delete w;
        }
        
        std::cout << "Outputing to file\n";
        ofs << "A*\n";
        for (std::pair<DWGraph::weight_t, long long> pair : distancesAndTimes) ofs << pair.first << "," << pair.second / nValuesInserted[pair.first] << ",\n";
    }

    {
        std::cout << "Running 1st Iteration analysis\n";
        std::vector<int> sizes = {2, 4, 6, 8, 10, 20, 40, 60, 80, 100, 200, 400, 600, 800, 1000};
        std::vector<InputGenerator> inputs;
        std::vector<std::pair<int, long long>> firstIterationTimes;
        for (int i : sizes) {
            std::ostringstream oss; oss << "c" << i << ".clients";
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
            it.initialize(&M, "../resources/it1_01.vans", inputs.at(i).getOutputPath(), "r.rides");
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
        remove("r.rides");
    }
    
    {
        std::cout << "Running 2nd Iteration analysis\n";
        std::vector<int> sizes = {2, 4, 6, 8, 10, 20, 40, 60, 80, 100, 200, 400, 600, 800, 1000};
        std::vector<InputGenerator> inputs;
        std::vector<std::pair<int, long long>> secondIterationTimes;
        for (int i : sizes) {
            std::ostringstream oss; oss << "c" << i << ".clients";
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
            it.initialize(&M, "../resources/it2_01.vans", inputs.at(i).getOutputPath(), "r.rides");
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
        remove("r.rides");
    }
*/
    {
        std::cout << "Running VStripes init analysis\n";
        std::cout << "Generating grids...\n";
        std::vector<std::list<coord_t>> grids;
        std::vector<size_t> sizes = {
            (size_t)sqrt(  100),
            (size_t)sqrt(  250),
            (size_t)sqrt(  500),
            (size_t)sqrt(  1000),
            (size_t)sqrt(  2000),
            (size_t)sqrt(  3000),
            (size_t)sqrt(  4000),
            (size_t)sqrt(  5000),
            (size_t)sqrt(  6000),
            (size_t)sqrt(  7000),
            (size_t)sqrt(  8000),
            (size_t)sqrt(  9000),
            (size_t)sqrt( 10000),
            (size_t)sqrt( 11000),
            (size_t)sqrt( 12000),
            (size_t)sqrt( 13000),
            (size_t)sqrt( 14000),
            (size_t)sqrt( 15000),
            (size_t)sqrt( 16000),
            (size_t)sqrt( 17000),
            (size_t)sqrt( 18000),
            (size_t)sqrt( 19000),
            (size_t)sqrt( 20000),
            (size_t)sqrt( 21000),
            (size_t)sqrt( 22000),
            (size_t)sqrt( 23000),
            (size_t)sqrt( 24000),
            (size_t)sqrt( 25000),
            (size_t)sqrt( 30000),
            (size_t)sqrt( 35000),
            (size_t)sqrt( 40000),
            (size_t)sqrt( 45000),
            (size_t)sqrt( 50000),
            (size_t)sqrt( 55000),
            (size_t)sqrt( 60000),
            (size_t)sqrt( 65000),
            (size_t)sqrt( 70000),
            (size_t)sqrt( 75000),
            (size_t)sqrt( 80000),
            (size_t)sqrt( 85000),
            (size_t)sqrt( 90000),
            (size_t)sqrt( 95000),
            (size_t)sqrt(100000),
            (size_t)sqrt(110000),
            (size_t)sqrt(120000),
            (size_t)sqrt(130000),
            (size_t)sqrt(140000),
            (size_t)sqrt(150000),
            (size_t)sqrt(160000),
            (size_t)sqrt(170000),
            (size_t)sqrt(180000),
            (size_t)sqrt(190000),
            (size_t)sqrt(200000),
            (size_t)sqrt(210000),
            (size_t)sqrt(220000),
            (size_t)sqrt(230000),
            (size_t)sqrt(240000),
            (size_t)sqrt(250000),
            (size_t)sqrt(260000),
            (size_t)sqrt(270000),
            (size_t)sqrt(280000),
            (size_t)sqrt(290000),
            (size_t)sqrt(300000),
            (size_t)sqrt(310000),
            (size_t)sqrt(320000),
            (size_t)sqrt(330000),
            (size_t)sqrt(340000),
            (size_t)sqrt(350000),
            (size_t)sqrt(360000),
            (size_t)sqrt(370000),
            (size_t)sqrt(380000),
            (size_t)sqrt(390000),
            (size_t)sqrt(400000),
            (size_t)sqrt(410000),
            (size_t)sqrt(420000),
            (size_t)sqrt(430000),
            (size_t)sqrt(440000),
            (size_t)sqrt(450000),
            (size_t)sqrt(460000),
            (size_t)sqrt(470000),
            (size_t)sqrt(480000),
            (size_t)sqrt(490000),
            (size_t)sqrt(500000),
            (size_t)sqrt(510000),
            (size_t)sqrt(520000),
            (size_t)sqrt(530000),
            (size_t)sqrt(540000),
            (size_t)sqrt(550000),
            (size_t)sqrt(560000),
            (size_t)sqrt(570000),
            (size_t)sqrt(580000),
            (size_t)sqrt(590000),
            (size_t)sqrt(600000),
            (size_t)sqrt(610000),
            (size_t)sqrt(620000),
            (size_t)sqrt(630000),
            (size_t)sqrt(640000),
            (size_t)sqrt(650000),
            (size_t)sqrt(660000),
            (size_t)sqrt(670000),
            (size_t)sqrt(680000),
            (size_t)sqrt(690000),
            (size_t)sqrt(700000),
            (size_t)sqrt(710000),
            (size_t)sqrt(720000),
            (size_t)sqrt(730000),
            (size_t)sqrt(740000),
            (size_t)sqrt(750000),
            (size_t)sqrt(760000),
            (size_t)sqrt(770000),
            (size_t)sqrt(780000),
            (size_t)sqrt(790000),
            (size_t)sqrt(800000),
            (size_t)sqrt(810000),
            (size_t)sqrt(820000),
            (size_t)sqrt(830000),
            (size_t)sqrt(840000),
            (size_t)sqrt(850000),
            (size_t)sqrt(860000),
            (size_t)sqrt(870000),
            (size_t)sqrt(880000),
            (size_t)sqrt(890000),
            (size_t)sqrt(900000),
            (size_t)sqrt(910000),
            (size_t)sqrt(920000),
            (size_t)sqrt(930000),
            (size_t)sqrt(940000),
            (size_t)sqrt(950000),
            (size_t)sqrt(960000),
            (size_t)sqrt(970000),
            (size_t)sqrt(980000),
            (size_t)sqrt(990000),
            (size_t)sqrt(1000000),
            };
        for (size_t size : sizes){
            std::list<coord_t> x;
            for(size_t i = 0 ; i < size ; ++i)
                for (size_t j = 0 ; j < size ; ++j)
                    x.push_back(coord_t(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/41.3112)) + 41.0055 , static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/8.4925)) + 8.7523 - 10));
            grids.push_back(x);
        }

        /*
        std::cout << "Node varying\n";

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
*/

        std::cout << "Query times\n";
        
        std::vector<std::pair<int, double>> VStripesQueryTimes;
        for (size_t i = 0 ; i < sizes.size() ; ++i){
            std::cout << sizes.at(i) << std::endl;
            VStripes vs(0.025);
            vs.initialize(grids.at(i));
            vs.run();
            coord_t point(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/41.3112)) + 41.0055 , static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/8.4925)) + 8.7523 - 10);
            auto start_time = hrc::now();
            for (long j = 0 ; j < 1000000 ; j++) vs.getClosestPoint(point);
            auto finish_time = hrc::now();
            long long execution_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count();
            VStripesQueryTimes.push_back(std::make_pair(sizes.at(i)*sizes.at(i), (double)execution_time/1000000));
        }
        std::cout << "Outputing to file\n";
        ofs << "VStripes Query Iteration\n";
        for (std::pair<int, double> pair : VStripesQueryTimes) ofs << pair.first << "," << pair.second << ",\n";
/*
        std::cout << "Delta varying\n";

        std::list<coord_t> grid = grids.at(14);
        std::vector<coord_t::deg_t> deltas = {0.001, 0.005, 0.01, 0.025, 0.05, 0.1, 0.2, 0.25};
        std::vector<std::pair<double, long long>> vStripesDeltasIterationTimes;
        for (size_t i = 0 ; i < deltas.size() ; ++i){
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
        */
    }


    ofs.close();
    return 0;
}