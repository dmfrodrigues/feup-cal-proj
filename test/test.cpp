#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Astar.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "ShortestPathAll.h"
#include "Kosaraju.h"
#include "KosarajuV.h"
#include "Tarjan.h"
#include "FloydWarshall.h"
#include "NearestNeighbour.h"
#include "HeldKarp.h"


TEST_CASE("Depth-First Search", "[reachability-dfs]"){
    DUGraph G;  
    for (size_t i = 0 ; i < 9 ; i++) G.addNode(i);
    G.addEdge(0,1); G.addEdge(1,2); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,0);
    G.addEdge(4,5); G.addEdge(5,6); G.addEdge(6,4); G.addEdge(7,6); G.addEdge(7,8);

    Reachability *r = new DFS();
    r->initialize(&G, 0);
    r->run();
    
    REQUIRE(r->is_reachable(0) == true );
    REQUIRE(r->is_reachable(1) == true );
    REQUIRE(r->is_reachable(2) == true );
    REQUIRE(r->is_reachable(3) == true );
    REQUIRE(r->is_reachable(4) == true );
    REQUIRE(r->is_reachable(5) == true );
    REQUIRE(r->is_reachable(6) == true );
    REQUIRE(r->is_reachable(7) == false);
    REQUIRE(r->is_reachable(8) == false);

    delete r;

}

TEST_CASE("Graph transpose", "[graph-transpose]"){
    DUGraph G;  
    for (size_t i = 0 ; i < 9 ; i++) G.addNode(i);
    G.addEdge(0,1); G.addEdge(1,2); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,0);
    G.addEdge(4,5); G.addEdge(5,6); G.addEdge(6,4); G.addEdge(7,6); G.addEdge(7,8);
    G = G.getTranspose();

    REQUIRE(G.getNodes() == std::list<DUGraph::node_t>({0, 1, 2, 3, 4, 5, 6, 7, 8}));
    REQUIRE(G.getAdj(0)  == std::list<DUGraph::node_t>({3}));
    REQUIRE(G.getAdj(1)  == std::list<DUGraph::node_t>({0}));
    REQUIRE(G.getAdj(2)  == std::list<DUGraph::node_t>({1}));
    REQUIRE(G.getAdj(3)  == std::list<DUGraph::node_t>({2}));
    REQUIRE(G.getAdj(4)  == std::list<DUGraph::node_t>({2,6}));
    REQUIRE(G.getAdj(5)  == std::list<DUGraph::node_t>({4}));
    REQUIRE(G.getAdj(6)  == std::list<DUGraph::node_t>({5, 7}));
    REQUIRE(G.getAdj(7)  == std::list<DUGraph::node_t>({}));
    REQUIRE(G.getAdj(8)  == std::list<DUGraph::node_t>({7}));
}


TEST_CASE("DFS on transpose", "[dfs-transpose]"){
    DUGraph G;  
    for (size_t i = 0 ; i < 9 ; i++) G.addNode(i);
    G.addEdge(0,1); G.addEdge(1,2); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,0);
    G.addEdge(4,5); G.addEdge(5,6); G.addEdge(6,4); G.addEdge(7,6); G.addEdge(7,8);
    G = G.getTranspose();

    Reachability *r = new DFS();
    r->initialize(&G, 0);
    r->run();
    
    REQUIRE(r->is_reachable(0) == true );
    REQUIRE(r->is_reachable(1) == true );
    REQUIRE(r->is_reachable(2) == true );
    REQUIRE(r->is_reachable(3) == true );
    REQUIRE(r->is_reachable(4) == false);
    REQUIRE(r->is_reachable(5) == false);
    REQUIRE(r->is_reachable(6) == false);
    REQUIRE(r->is_reachable(7) == false);
    REQUIRE(r->is_reachable(8) == false);

    delete r;
}


TEST_CASE("Floyd-Warshall", "[floyd-warshall]") {
    DWGraph::DWGraph G;
    for(int i = 0; i < 4; ++i) G.addNode(i);
    G.addEdge(0, 2, -2); G.addEdge(2, 3, 2); G.addEdge(3, 1, -1); G.addEdge(1, 0, 4);
    G.addEdge(1, 2, 3);

    FloydWarshall *fw = new FloydWarshall();
    fw->initialize(&G);
    fw->run();

    REQUIRE(std::list<DWGraph::node_t>({0, 2, 3, 1})    == fw->getPath(0, 1));
    REQUIRE(std::list<DWGraph::node_t>({0, 2})          == fw->getPath(0, 2));
    REQUIRE(std::list<DWGraph::node_t>({0, 2, 3})       == fw->getPath(0, 3));

    REQUIRE(std::list<DWGraph::node_t>({1, 0})          == fw->getPath(1, 0));
    REQUIRE(std::list<DWGraph::node_t>({1, 0, 2})       == fw->getPath(1, 2));
    REQUIRE(std::list<DWGraph::node_t>({1, 0, 2, 3})    == fw->getPath(1, 3));

    REQUIRE(std::list<DWGraph::node_t>({2, 3, 1, 0})    == fw->getPath(2, 0));
    REQUIRE(std::list<DWGraph::node_t>({2, 3, 1})       == fw->getPath(2, 1));
    REQUIRE(std::list<DWGraph::node_t>({2, 3})          == fw->getPath(2, 3));

    REQUIRE(std::list<DWGraph::node_t>({3, 1, 0})       == fw->getPath(3, 0));
    REQUIRE(std::list<DWGraph::node_t>({3, 1})          == fw->getPath(3, 1));
    REQUIRE(std::list<DWGraph::node_t>({3, 1, 0, 2})    == fw->getPath(3, 2));
    
    delete fw;
}


TEST_CASE("Dijkstra's algorithm", "[shortestpath-dijkstra]"){
    DWGraph::DWGraph G;
    for(int i = 0; i < 7; ++i) G.addNode(i);
    G.addEdge(0, 1, 1); G.addEdge(1, 2, 2); G.addEdge(0, 3, 5); G.addEdge(3, 4, 2);
    G.addEdge(2, 3, 1); G.addEdge(2, 5, 2); G.addEdge(4, 5, 3); G.addEdge(5, 6, 4);
    {
        ShortestPathOneMany *shortestPath = new Dijkstra();
        shortestPath->initialize(&G, 0);
        shortestPath->run();

        REQUIRE(std::list<DWGraph::node_t>({0               }) == shortestPath->getPath(0));
        REQUIRE(std::list<DWGraph::node_t>({0, 1            }) == shortestPath->getPath(1));
        REQUIRE(std::list<DWGraph::node_t>({0, 1, 2         }) == shortestPath->getPath(2));
        REQUIRE(std::list<DWGraph::node_t>({0, 1, 2, 3      }) == shortestPath->getPath(3));
        REQUIRE(std::list<DWGraph::node_t>({0, 1, 2, 3, 4   }) == shortestPath->getPath(4));
        REQUIRE(std::list<DWGraph::node_t>({0, 1, 2, 5      }) == shortestPath->getPath(5));
        REQUIRE(std::list<DWGraph::node_t>({0, 1, 2, 5, 6   }) == shortestPath->getPath(6));

        REQUIRE(0 == shortestPath->getPathWeight(0));
        REQUIRE(1 == shortestPath->getPathWeight(1));
        REQUIRE(3 == shortestPath->getPathWeight(2));
        REQUIRE(4 == shortestPath->getPathWeight(3));
        REQUIRE(6 == shortestPath->getPathWeight(4));
        REQUIRE(5 == shortestPath->getPathWeight(5));
        REQUIRE(9 == shortestPath->getPathWeight(6));

        delete shortestPath;
    }
    {
        ShortestPathOneMany *shortestPath = new Dijkstra();
        shortestPath->initialize(&G, 1);
        shortestPath->run();

        REQUIRE(std::list<DWGraph::node_t>({                }) == shortestPath->getPath(0));
        REQUIRE(std::list<DWGraph::node_t>({1               }) == shortestPath->getPath(1));
        REQUIRE(std::list<DWGraph::node_t>({1, 2            }) == shortestPath->getPath(2));
        REQUIRE(std::list<DWGraph::node_t>({1, 2, 3         }) == shortestPath->getPath(3));
        REQUIRE(std::list<DWGraph::node_t>({1, 2, 3, 4      }) == shortestPath->getPath(4));
        REQUIRE(std::list<DWGraph::node_t>({1, 2, 5         }) == shortestPath->getPath(5));
        REQUIRE(std::list<DWGraph::node_t>({1, 2, 5, 6      }) == shortestPath->getPath(6));

        REQUIRE(DWGraph::INF == shortestPath->getPathWeight(0));
        REQUIRE(0 == shortestPath->getPathWeight(1));
        REQUIRE(2 == shortestPath->getPathWeight(2));
        REQUIRE(3 == shortestPath->getPathWeight(3));
        REQUIRE(5 == shortestPath->getPathWeight(4));
        REQUIRE(4 == shortestPath->getPathWeight(5));
        REQUIRE(8 == shortestPath->getPathWeight(6));

        delete shortestPath;
    }
}

TEST_CASE("Dijkstra's algorithm for all", "[shortestpathall-dijkstra]"){
    DWGraph::DWGraph G;
    for(int i = 0; i < 7; ++i) G.addNode(i);
    G.addEdge(0, 1, 1); G.addEdge(1, 2, 2); G.addEdge(0, 3, 5); G.addEdge(3, 4, 2);
    G.addEdge(2, 3, 1); G.addEdge(2, 5, 2); G.addEdge(4, 5, 3); G.addEdge(5, 6, 4);
    
    ShortestPathAll *shortestPath = new ShortestPathAll::FromOneMany(new Dijkstra(), 8);
    shortestPath->initialize(&G);
    shortestPath->run();

    std::vector< std::vector<DWGraph::weight_t> > dist = {
        {0, 1, 3, 4, 6, 5, 9},
        {DWGraph::INF, 0, 2, 3, 5, 4, 8},
        {DWGraph::INF, DWGraph::INF, 0, 1, 3, 2, 6},
        {DWGraph::INF, DWGraph::INF, DWGraph::INF, 0, 2, 5, 9},
        {DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, 0, 3, 7},
        {DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, 0, 4},
        {DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, DWGraph::INF, 0}
    };

    for(size_t s = 0; s < dist.size(); ++s){
        for(size_t d = 0; d < dist[s].size(); ++d){
            REQUIRE(dist[s][d] == shortestPath->getPathWeight(s, d));
        }
    }

    delete shortestPath;
}

TEST_CASE("A* algorithm", "[shortestpath-astar]"){
    DWGraph::DWGraph G;
    for(int i = 0; i < 7; ++i) G.addNode(i);
    G.addEdge(0, 1, 1); G.addEdge(1, 2, 2); G.addEdge(0, 3, 5); G.addEdge(3, 4, 2);
    G.addEdge(2, 3, 1); G.addEdge(2, 5, 2); G.addEdge(4, 5, 3); G.addEdge(5, 6, 4);
    
    ShortestPath *shortestPath = new Astar();
    shortestPath->initialize(&G, 0, 6);
    shortestPath->run();

    REQUIRE(9 == shortestPath->getPathWeight());
    REQUIRE(std::list<DWGraph::node_t>({0, 1, 2, 5, 6   }) == shortestPath->getPath());

    delete shortestPath;
}

TEST_CASE("Kosaraju variant testing", "[scc-kosarajuv]"){
    DUGraph Graph;  
    for (size_t i = 0 ; i < 9 ; i++) Graph.addNode(i);
    Graph.addEdge(0,1); Graph.addEdge(1,2); Graph.addEdge(2,3); Graph.addEdge(2,4); Graph.addEdge(3,0);
    Graph.addEdge(4,5); Graph.addEdge(5,6); Graph.addEdge(6,4); Graph.addEdge(7,6); Graph.addEdge(7,8);

    DFS r;
    KosarajuV k(&r); 
    k.initialize(&Graph, 0); 
    k.run();

    REQUIRE(k.is_scc(0) == true);
    REQUIRE(k.is_scc(1) == true);
    REQUIRE(k.is_scc(2) == true);
    REQUIRE(k.is_scc(3) == true);

    REQUIRE(k.is_scc(4) == false);
    REQUIRE(k.is_scc(5) == false);
    REQUIRE(k.is_scc(6) == false);

    REQUIRE(k.is_scc(7) == false);
    REQUIRE(k.is_scc(8) == false);

}

TEST_CASE("Classic Kosaraju testing", "[SCC-KOSARAJU]"){
    DUGraph Graph;  
    for (size_t i = 0 ; i < 9 ; i++) Graph.addNode(i);
    Graph.addEdge(0,1); Graph.addEdge(1,2); Graph.addEdge(2,3); Graph.addEdge(2,4); Graph.addEdge(3,0);
    Graph.addEdge(4,5); Graph.addEdge(5,6); Graph.addEdge(6,4); Graph.addEdge(7,6); Graph.addEdge(7,8);

    Kosaraju k; 
    k.initialize(&Graph); 
    k.run();
    REQUIRE(k.get_scc(0) == k.get_scc(1));
    REQUIRE(k.get_scc(0) == k.get_scc(2));
    REQUIRE(k.get_scc(0) == k.get_scc(3));

    REQUIRE(k.get_scc(4) == k.get_scc(5));
    REQUIRE(k.get_scc(4) == k.get_scc(6));

    REQUIRE(k.get_scc(7) == 7);

    REQUIRE(k.get_scc(8) == 8);
}

TEST_CASE("Tarjan testing", "[SCC-TARJAN]"){
    DUGraph Graph;  
    for (size_t i = 0 ; i < 9 ; i++) Graph.addNode(i);
    Graph.addEdge(0,1); Graph.addEdge(1,2); Graph.addEdge(2,3); Graph.addEdge(2,4); Graph.addEdge(3,0);
    Graph.addEdge(4,5); Graph.addEdge(5,6); Graph.addEdge(6,4); Graph.addEdge(7,6); Graph.addEdge(7,8);

    Tarjan t; 
    t.initialize(&Graph); 
    t.run();
    REQUIRE(t.get_scc(0) == t.get_scc(1));
    REQUIRE(t.get_scc(0) == t.get_scc(2));
    REQUIRE(t.get_scc(0) == t.get_scc(3));

    REQUIRE(t.get_scc(4) == t.get_scc(5));
    REQUIRE(t.get_scc(4) == t.get_scc(6));

    REQUIRE(t.get_scc(7) == 7);

    REQUIRE(t.get_scc(8) == 8);
}

class regular_weight : public TravellingSalesman::weight_function{
private:
    const std::vector< std::vector<DWGraph::weight_t> > M;
public:
    regular_weight(const std::vector< std::vector<DWGraph::weight_t> > &M_):M(M_){}
    DWGraph::weight_t operator()(const std::unordered_multiset<DWGraph::node_t> &S, const DWGraph::node_t &u, const DWGraph::node_t &v) const{
        return M[u][v];
    }
};

TEST_CASE("Nearest Neighbour", "[NN]"){
    std::vector< std::vector<DWGraph::weight_t> > M = {
        {  0, 132, 217, 164,  58},
        {132,   0, 290, 201,  79},
        {217, 290,   0, 113, 303},
        {164, 201, 113,   0, 196},
        { 58,  79, 303, 196,   0}
    };
    std::list<DWGraph::node_t> nodes({0,1,2,3,4});
    regular_weight w(M);

    TravellingSalesman *tsp = new NearestNeighbour();
    
    tsp->initialize(&nodes, 0, &w);
    tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({0, 4, 1, 3, 2, 0}) == tsp->getTour() );

    tsp->initialize(&nodes, 1, &w);
    tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({1, 4, 0, 3, 2, 1}) == tsp->getTour() );

    tsp->initialize(&nodes, 2, &w);
    tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({2, 3, 0, 4, 1, 2}) == tsp->getTour() );

    tsp->initialize(&nodes, 3, &w);
    tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({3, 2, 0, 4, 1, 3}) == tsp->getTour() );

    tsp->initialize(&nodes, 4, &w);
    tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({4, 0, 1, 3, 2, 4}) == tsp->getTour() );

    delete tsp;
}

TEST_CASE("Held-Karp algorithm", "[tsp-heldkarp]"){
    DWGraph::DWGraph G;
    for(int i = 0; i < 4; ++i) G.addNode(i);
                        G.addEdge(1, 0,  2);G.addEdge(2, 0,  9);G.addEdge(3, 0, 10);
    G.addEdge(0, 1,  1);                    G.addEdge(2, 1,  6);G.addEdge(3, 1,  4);
    G.addEdge(0, 2, 15);G.addEdge(1, 2,  7);                    G.addEdge(3, 2,  8);
    G.addEdge(0, 3,  6);G.addEdge(1, 3, 12);G.addEdge(2, 3, 12);
    std::vector< std::vector< DWGraph::weight_t> > W({
        { 0, 2,  9, 10},
        { 1, 0,  6,  4},
        {15, 7,  0,  8},
        { 6, 3, 12,  0}
    });
    regular_weight w(W);
    REQUIRE(w({}, 0, 2) == 9);
    REQUIRE(w({}, 2, 3) == 8);
    REQUIRE(w({}, 3, 1) == 3);
    REQUIRE(w({}, 1, 0) == 1);
    
    std::list<DWGraph::node_t> nodes({0,1,2,3});

    HeldKarp *tsp = new HeldKarp();

    tsp->initialize(&nodes, 0, &w);
                                                                                                             REQUIRE(tsp->HK(0b0001, 0) ==  0);  
                                                                          REQUIRE(tsp->HK(0b0011, 1) ==  2); 
                                       REQUIRE(tsp->HK(0b0101, 2) ==  9);                                     
    REQUIRE(tsp->HK(0b1001, 3) == 10);                                                                        
                                       REQUIRE(tsp->HK(0b0111, 2) ==  8); REQUIRE(tsp->HK(0b0111, 1) == 16);  
    REQUIRE(tsp->HK(0b1011, 3) ==  6);                                    REQUIRE(tsp->HK(0b1011, 1) == 13);  
    
    REQUIRE(tsp->HK(0b1101, 3) == 17); REQUIRE(tsp->HK(0b1101, 2) == 22);                                     
    REQUIRE(tsp->HK(0b1111, 3) == 16); REQUIRE(tsp->HK(0b1111, 2) == 18); REQUIRE(tsp->HK(0b1111, 1) == 20);  
    tsp->run();
    auto path = tsp->getTour();
    REQUIRE(std::list<DWGraph::node_t>({0, 2, 3, 1, 0}) == path);
    std::vector<DWGraph::node_t> v(path.begin(), path.end());
    DWGraph::weight_t total_weight = 0;
    for(size_t i = 1; i < v.size(); ++i) total_weight += w({}, v[i-1], v[i]);
    REQUIRE(total_weight == 21);

    tsp->initialize(&nodes, 1, &w); tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({1, 0, 2, 3, 1}) == tsp->getTour());

    tsp->initialize(&nodes, 2, &w); tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({2, 3, 1, 0, 2}) == tsp->getTour());

    tsp->initialize(&nodes, 3, &w); tsp->run();
    REQUIRE(std::list<DWGraph::node_t>({3, 1, 0, 2, 3}) == tsp->getTour());

    delete tsp;
}
