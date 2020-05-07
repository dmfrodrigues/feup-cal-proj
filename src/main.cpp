#include "graphviewer.h"

int main(){
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->rearrange();
    return 0;
}
