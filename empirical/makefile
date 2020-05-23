STRUCTS_FLIB =../structures/lib/libstructures.a
ALGS_FLIB =../algorithms/lib/libalgorithms.a
UTILS_FLIB=../utils/lib/libutils.a

all: src/GraphGenerator.cpp src/main.cpp $(STRUCTS_FLIB) $(ALGS_FLIB) $(UTILS_FLIB)
	g++ -Wall -pthread -lrt -g -I./include -I../structures/include -I../algorithms/include -I../utils/include src/GraphGenerator.cpp src/main.cpp -o GraphGenerator -L../structures/lib -lstructures -L../algorithms/lib -lalgorithms -L../utils/lib -lutils

FORCE:

$(STRUCTS_FLIB): FORCE
	make -C ../structures

$(ALGS_FLIB): FORCE
	make -C ../algorithms

$(UTILS_FLIB): FORCE
	make -C ../utils

clean:
	rm -f GraphGenerator