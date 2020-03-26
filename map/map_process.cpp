#include <bits/stdc++.h>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

xml_node<> *find_tag(xml_node<> *p, const string &k) {
    xml_node<> *ret;
    for (ret = p->first_node("tag"); ret; ret = ret->next_sibling()) {
        if (k == ret->first_attribute("k")->value()) break;
    }
    return ret;
}

enum EdgeType : char{
    No          = 'n',
    Motorway    = 'M',
    Trunk       = 'T',
    Road        = 'R',
    Residential = 'r',
    Slow        = 's'
};

unordered_map<string, EdgeType> edge_accept = {
    {"motorway"         , EdgeType::Motorway},
    {"motorway_link"    , EdgeType::Motorway},
    {"trunk"            , EdgeType::Trunk},
    {"trunk_link"       , EdgeType::Trunk},
    {"primary"          , EdgeType::Road},
    {"primary_link"     , EdgeType::Road},
    {"secondary"        , EdgeType::Road},
    {"secondary_link"   , EdgeType::Road},
    {"tertiary"         , EdgeType::Road},
    {"tertiary_link"    , EdgeType::Road},
    {"unclassified"     , EdgeType::Road},
    {"residential"      , EdgeType::Residential},
    {"living_street"    , EdgeType::Slow},
    {"road"             , EdgeType::Slow},
    {"services"         , EdgeType::Slow},
    {"bus_stop"         , EdgeType::Slow}
};
unordered_set<string> edge_reject = {
    "steps",        "pedestrian", "footway",   "cycleway", "track",
    "construction", "path",       "bridleway", "platform", "raceway",
    "elevator",     "proposed",   "planned"};
unordered_set<string> service_accept = {"driveway", "parking_aisle", "alley"};
unordered_set<string> service_reject = {"campground", "emergency_access",
                                        "drive-through"};
EdgeType get_edge_type(xml_node<> *it) {
    auto phighway = find_tag(it, "highway");
    auto pservice = find_tag(it, "service");
    if (phighway == NULL) return EdgeType::No;
    if (edge_reject.find(phighway->first_attribute("v")->value()) !=
        edge_reject.end())
        return EdgeType::No;
    if (edge_accept.find(phighway->first_attribute("v")->value()) !=
        edge_accept.end())
        return edge_accept[phighway->first_attribute("v")->value()];
    if (pservice == NULL) return EdgeType::No;
    if (string(phighway->first_attribute("v")->value()) == "service") {
        if (service_reject.find(pservice->first_attribute("v")->value()) !=
            service_reject.end())
            return EdgeType::No;
        if (service_accept.find(pservice->first_attribute("v")->value()) !=
            service_accept.end())
            return EdgeType::Slow;
    }
    cerr << it->first_attribute("id")->value() << " rejected "
         << phighway->first_attribute("v")->value() << "\n";
    return EdgeType::No;
}

list<string> get_edge_nodes(xml_node<> *it){
    list<string> nodes_edge;
    for(auto j = it->first_node("nd"); string(j->name()) == "nd"; j = j->next_sibling()){
        nodes_edge.push_back(j->first_attribute("ref")->value());
    }
    return nodes_edge;
}

enum EdgeDirection {
    Front = 1,
    Both = 0,
    Back = -1
};

EdgeDirection get_edge_direction(xml_node<> *it){
    auto p = find_tag(it, "oneway");
    if(!p) return EdgeDirection::Both;
    if(string(p->first_attribute("v")->value()) == "yes") return EdgeDirection::Front;
    if(string(p->first_attribute("v")->value()) == "no") return EdgeDirection::Both;
    if(string(p->first_attribute("v")->value()) == "reversible") return EdgeDirection::Both;
    return EdgeDirection::Both;
}

typedef int Speed;
Speed get_edge_speed(xml_node<> *it){
    auto p = find_tag(it, "maxspeed");
    if(!p) return -1;
    Speed s;
    if(sscanf(p->first_attribute("v")->value(), "%d", &s) != 1) return -1;
    return s;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    char *text = NULL; {
        string all = "";
        string buf;
        while (getline(cin, buf)) {
            all += buf + "\n";
        }
        text = new char[all.size() + 1];
        strcpy(text, all.c_str());
    }
    xml_document<> doc;
    doc.parse<0>(text);

    int num_ways = 0;
    unordered_set<string> good_nodes;
    list<string> edges;{
        for (auto it = doc.first_node()->first_node("way"); string(it->name()) == "way"; it = it->next_sibling()) {
            EdgeType t = get_edge_type(it);
            if (t == EdgeType::No) continue;
            ++num_ways;
            list<string> nodes_edge = get_edge_nodes(it);
            EdgeDirection d = get_edge_direction(it);
            string sp = to_string(get_edge_speed(it));
            if(d == EdgeDirection::Back){
                reverse(nodes_edge.begin(), nodes_edge.end());
                d = EdgeDirection::Front;
            }
            string prev = *nodes_edge.begin(); good_nodes.insert(prev);
            for(auto it = ++nodes_edge.begin(); it != nodes_edge.end(); prev = *(it++)){
                edges.push_back("(" + prev + ", " + string(*it) + ", " + char(t) + ", " + sp + ")");
                good_nodes.insert(string(*it));
            }
            if(d == EdgeDirection::Both){
                prev = *nodes_edge.rbegin();
                for(auto it = ++nodes_edge.rbegin(); it != nodes_edge.rend(); prev = *(it++)){
                    edges.push_back("(" + prev + ", " + string(*it) + ", " + char(t) + ", " + sp + ")");
                }
            }
        }
    }

    list<string> nodes;{
        for (auto it = doc.first_node()->first_node("node"); string(it->name()) == "node"; it = it->next_sibling()) {
            if(good_nodes.find(string(it->first_attribute("id")->value())) != good_nodes.end()){
                nodes.push_back("(" +
                                string(it->first_attribute("id")->value()) + ", " +
                                string(it->first_attribute("lat")->value()) + ", " +
                                string(it->first_attribute("lon")->value()) + ")");
            }
        }
    }
    {
        string nodes_path = string(argv[1]) + ".nodes";
        ofstream os(nodes_path);
        os << nodes.size() << "\n";
        for (const string &s : nodes) os << s << "\n";
    }
    {
        cerr << "Num ways: " << num_ways << endl;
        string edges_path = string(argv[1]) + ".edges";
        ofstream os(edges_path);
        os << edges.size() << "\n";
        for (const string &s : edges) os << s << "\n";
    }
    return 0;
}
