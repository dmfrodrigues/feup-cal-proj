#include "DWGraph.h"

class GraphGenerator {
private:
    DWGraph::DWGraph G;
    int numNodes;

public:
    GraphGenerator(int numNodes);
    void run();
    int getNum() const;
    DWGraph::DWGraph getDWGraph() const;
};