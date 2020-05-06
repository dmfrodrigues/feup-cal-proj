#include "DWGraph.h"

DWGraph::DWGraph(){}

void DWGraph::addNode(node_t u){
    if(adj.find(u) != adj.end())
        throw std::invalid_argument("Node already exists");
    nodes.push_back(u);
    adj[u] = std::list<Edge>();
}

void DWGraph::addEdge(node_t u, node_t v, weight_t w){
    if(adj.find(u) == adj.end() || adj.find(v) == adj.end())
        throw std::invalid_argument("Node does not exist");
    adj[u].push_back(Edge(v, w));
}

const std::list<DWGraph::node_t>& DWGraph::getNodes() const{
    return nodes;
}

const std::list<DWGraph::Edge>& DWGraph::getAdj(node_t u) const{
    return adj.at(u);
}
