#ifndef KOSARAJU_VARIANT_H_INCLUDED
#define KOSARAJU_VARIANT_H_INCLUDED

#include "SCCnode.h"
#include "Reachability.h"

class KosarajuV : public SCCnode{
private:
    const DUGraph *G;
    DUGraph::node_t s;
    Reachability *r;
    std::unordered_map<DUGraph::node_t, bool> isSCC;
public:
    KosarajuV(Reachability *r);
    void initialize(const DUGraph *G, DUGraph::node_t s);
    void run();
    bool is_scc(DUGraph::node_t v) const;
};

#endif //KOSARAJU_VARIANT_H_INCLUDED
