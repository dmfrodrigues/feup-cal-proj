STRUCTS_FLIB=../structures/lib/libstructures.a
ALGS_FLIB=../algorithms/lib/libalgorithms.a
UTILS_FLIB=../utils/lib/libutils.a
GV_FLIB=../GraphViewer/lib/libgraphviewer.a
MAIN_FLIB=../lib/libmain.a

all: src/GraphGenerator.cpp src/main.cpp $(STRUCTS_FLIB) $(ALGS_FLIB) $(UTILS_FLIB) $(GV_FLIB) $(MAIN_FLIB)
	g++ -Wall -pthread -lrt -g -I../include -I./include -I../structures/include -I../algorithms/include -I../utils/include -I../GraphViewer/cpp src/GraphGenerator.cpp -I../resources/include ../resources/src/input_generator.cpp src/main.cpp -o GenerateEmpirical -L../lib -lmain -L../algorithms/lib -lalgorithms -L../structures/lib -lstructures -L../utils/lib -lutils -L../GraphViewer/lib -lgraphviewer

FORCE:

$(STRUCTS_FLIB): FORCE
	make -C ../structures

$(ALGS_FLIB): FORCE
	make -C ../algorithms

$(UTILS_FLIB): FORCE
	make -C ../utils

$(GV_FLIB): FORCE
	make -C ../GraphViewer

$(MAIN_FLIB): FORCE
	make -C ..

clean:
	rm -f GenerateEmpirical