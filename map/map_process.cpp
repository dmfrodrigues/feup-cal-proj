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
    edge_type_t edgeType;
    way_t(xml_node<> *it, edge_type_t eType){
        edgeType = eType;
        get_way(it);
        dir = get_dir(it);
        speed = get_speed(it);
        if(dir == dir_t::Back){
            reverse();
            dir = dir_t::Front;
        }
    }
    size_t getNumWays() const{
        switch(dir){
            case dir_t::Front: return 1;
            case dir_t::Back: return 1;
            case dir_t::Both: return 2;
            default: throw invalid_argument("");
        }
    }
};

ostream& operator<<(ostream &os, const way_t &w){
    if(w.dir == dir_t::Front || w.dir == dir_t::Both){
        os << char(w.edgeType) << " " << w.speed << " " << w.size();
        for(auto it = w.begin(); it != w.end(); ++it){
            os << "\n" << *it;
        }
    }
    if(w.dir == dir_t::Back || w.dir == dir_t::Both){
        os << char(w.edgeType) << " " << w.speed << " " << w.size();
        for(auto it = w.rbegin(); it != w.rend(); ++it){
            os << "\n" << *it;
        }
    }
        
    return os;
}

unordered_map<string, edge_type_t> edge_accept = {
    {"motorway"         , edge_type_t::MOTORWAY},
    {"motorway_link"    , edge_type_t::MOTORWAY},
    {"trunk"            , edge_type_t::TRUNK},
    {"trunk_link"       , edge_type_t::TRUNK},
    {"primary"          , edge_type_t::PRIMARY},
    {"primary_link"     , edge_type_t::PRIMARY},
    {"secondary"        , edge_type_t::SECONDARY},
    {"secondary_link"   , edge_type_t::SECONDARY},
    {"tertiary"         , edge_type_t::TERTIARY},
    {"tertiary_link"    , edge_type_t::TERTIARY},
    {"unclassified"     , edge_type_t::ROAD},
    {"residential"      , edge_type_t::RESIDENTIAL},
    {"living_street"    , edge_type_t::SLOW},
    {"road"             , edge_type_t::SLOW},
    {"services"         , edge_type_t::SLOW},
    {"bus_stop"         , edge_type_t::SLOW}
};
unordered_set<string> edge_reject = {
    "steps",        "pedestrian", "footway",   "cycleway", "track",
    "construction", "path",       "bridleway", "platform", "raceway",
    "elevator",     "proposed",   "planned"};
unordered_set<string> service_accept = {"driveway", "parking_aisle", "alley"};
unordered_set<string> service_reject = {"campground", "emergency_access",
                                        "drive-through"};
edge_type_t get_edge_type(xml_node<> *it) {
    auto phighway = find_tag(it, "highway");
    auto pservice = find_tag(it, "service");
    if (phighway == NULL) return edge_type_t::NO;
    if (edge_reject.find(phighway->first_attribute("v")->value()) != edge_reject.end()) return edge_type_t::NO;
    if (edge_accept.find(phighway->first_attribute("v")->value()) != edge_accept.end()) return edge_accept[phighway->first_attribute("v")->value()];
    if (pservice == NULL) return edge_type_t::NO;
    if (string(phighway->first_attribute("v")->value()) == "service") {
        if (service_reject.find(pservice->first_attribute("v")->value()) !=
            service_reject.end())
            return edge_type_t::NO;
        if (service_accept.find(pservice->first_attribute("v")->value()) !=
            service_accept.end())
            return edge_type_t::SLOW;
    }
    cerr << it->first_attribute("id")->value() << " rejected "
         << phighway->first_attribute("v")->value() << "\n";
    return edge_type_t::NO;
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
            edge_type_t t = get_edge_type(it); if (t == edge_type_t::NO) continue;
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
        size_t sz = 0;
        for(const way_t &w: ways){
            sz += w.getNumWays();
        }
        os << sz << "\n";
        int i = 0;
        for(const way_t &w: ways){
            os << w << "\n";
        }
    }
    
    return 0;
}
