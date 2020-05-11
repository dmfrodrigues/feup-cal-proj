#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "DFS.h"
#include "Kosaraju.h"
#include "KosarajuV.h"

// TEST_CASE("Human-readable name", "[shortname]"){
//     REQUIRE(true);
// }

// TEST_CASE("Whatever's algorithm", "[whatever-alg]"){
//     REQUIRE(true);
// }

TEST_CASE("Kosaraju variant testing", "[SCC-KOSARAJUV]"){
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
