STRUCTS_FLIB=../structures/lib/libstructures.a
ALGS_FLIB=../algorithms/lib/libalgorithms.a
UTILS_FLIB=../utils/lib/libutils.a
GV_FLIB=../GraphViewer/lib/libgraphviewer.a

all: src/GraphGenerator.cpp src/main.cpp $(STRUCTS_FLIB) $(ALGS_FLIB) $(UTILS_FLIB) $(GV_FLIB)
	g++ -Wall -pthread -lrt -g -I../include -I./include -I../structures/include -I../algorithms/include -I../utils/include -I../GraphViewer/cpp src/GraphGenerator.cpp -I../resources/include ../src/RoutingHeuristic.cpp ../src/MapViewer.cpp ../src/MapGraph.cpp ../src/Iteration1.cpp ../src/Client.cpp ../resources/src/input_generator.cpp src/main.cpp -o GraphGenerator -L../structures/lib -lstructures -L../algorithms/lib -lalgorithms -L../utils/lib -lutils -L../GraphViewer/lib -lgraphviewer

FORCE:

$(STRUCTS_FLIB): FORCE
	make -C ../structures

$(ALGS_FLIB): FORCE
	make -C ../algorithms

$(UTILS_FLIB): FORCE
	make -C ../utils

$(GV_FLIB): FORCE
	make -C ../GraphViewer

clean:
	rm -f GraphGenerator