#ifndef POINT_GENERATOR_H_INCLUDED
#define POINT_GENERATOR_H_INCLUDED


class PointGenerator {
private:
    DWGraph::DWGraph *G;
    int numNodes;

public:
    PointGenerator(int numNodes);
    void run();
    int getNum() const;
    DWGraph::DWGraph* getDWGraph() const;
};

#endif //POINT_GENERATOR_H_INCLUDED