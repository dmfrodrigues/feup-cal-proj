#include <bits/stdc++.h>
#include "rapidxml.hpp"
#include "EdgeType.h"

using namespace std;
using namespace rapidxml;

xml_node<> *find_tag(xml_node<> *p, const string &k) {
    xml_node<> *ret;
    for (ret = p->first_node("tag"); ret; ret = ret->next_sibling()) {
        if (k == ret->first_attribute("k")->value()) break;
    }
    return ret;
}

enum dir_t {
    Front = 1,
    Both = 0,
    Back = -1
};

typedef string node_id_t;

struct node_t{
    node_id_t id;
    double lat;
    double lon;
    node_t(xml_node<> *it){
        id = it->first_attribute("id")->value();
        lat = atof(it->first_attribute("lat")->value());
        lon = atof(it->first_attribute("lon")->value());
    }
};

ostream& operator<<(ostream &os, const node_t &u){
    os << fixed << setprecision(10);
    os << u.id << " " << u.lat << " " << u.lon;
    return os;
}

typedef int speed_t;

class way_t : public list<node_id_t> {
private:
    void get_way(xml_node<> *it){
        for(auto j = it->first_node("nd"); string(j->name()) == "nd"; j = j->next_sibling()){
            this->push_back(j->first_attribute("ref")->value());
        }
    }

    dir_t get_dir(xml_node<> *it){
        auto p = find_tag(it, "oneway");
        if(!p) return dir_t::Both;
        if(string(p->first_attribute("v")->value()) == "yes") return dir_t::Front;
        if(string(p->first_attribute("v")->value()) == "no") return dir_t::Both;
        if(string(p->first_attribute("v")->value()) == "reversible") return dir_t::Both;
        return dir_t::Both;
    }

    speed_t get_speed(xml_node<> *it){
        auto p = find_tag(it, "maxspeed");
        if(!p) return -1;
        speed_t s;
        if(sscanf(p->first_attribute("v")->value(), "%d", &s) != 1) return -1;
        return s;
    }
public:
    dir_t dir;
    speed_t speed;
    EdgeType edgeType;
    way_t(xml_node<> *it, EdgeType eType){
        edgeType = eType;
        get_way(it);
        dir = get_dir(it);
        speed = get_speed(it);
        if(dir == dir_t::Back){
            reverse();
            dir = dir_t::Front;
        }
    }
};

ostream& operator<<(ostream &os, const way_t &w){
    os << w.dir << " " << char(w.edgeType) << " " << w.speed << " " << w.size();
    for(auto it = w.begin(); it != w.end(); ++it){
        os << "\n" << *it;
    }
    return os;
}

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

    set<node_id_t> node_ids;
    list<way_t> ways;
    
    {
        for (auto it = doc.first_node()->first_node("way"); string(it->name()) == "way"; it = it->next_sibling()) {
            EdgeType t = get_edge_type(it); if (t == EdgeType::No) continue;
            way_t way(it, t); ways.push_back(way);
            node_ids.insert(way.begin(), way.end());
        }
    }

    list<node_t> nodes;{
        for (auto it = doc.first_node()->first_node("node"); string(it->name()) == "node"; it = it->next_sibling()) {
            node_t node(it);
            if(node_ids.find(node.id) != node_ids.end()){
                nodes.push_back(node);
            }            
        }
    }
    {
        ofstream os(string(argv[1]) + ".nodes");
        os << nodes.size() << "\n";
        for(const node_t &u: nodes) os << u << "\n";
    }
    {
        ofstream os(string(argv[1]) + ".edges");
        os << ways.size() << "\n";
        for(const way_t &w: ways) os << w << "\n";
    }
    
    return 0;
}
