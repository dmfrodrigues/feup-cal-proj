#include "DWGraph.h"

DWGraph::Edge::Edge(node_t v, weight_t w):v(v),w(w){}

void DWGraph::assert_integrity() const{
    if(nodes.size() != adj.size()) throw std::logic_error("");
    std::unordered_set<node_t> nodes_s(nodes.begin(), nodes.end());
    if(nodes.size() != nodes_s.size()) throw std::logic_error("");
    for(const auto &Adj: adj){
        if(!nodes_s.count(Adj.first)) throw std::logic_error("");
        for(const auto &e: Adj.second){
            if(!nodes_s.count(e.v)) throw std::logic_error("");
        }
    }
}

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

DWGraph::operator DUGraph() const{
    DUGraph G;
    for(const node_t &u: getNodes()){
        G.addNode(u);
    }
    for(const node_t &u: getNodes()){
        for(const Edge &e: getAdj(u)){
            G.addEdge(u, e.v);
        }
    }
    return G;
}
