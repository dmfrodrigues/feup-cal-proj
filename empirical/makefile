STRUCTS_FLIB = ../structures/lib/libstructures.a
ALGS_FLIB = ../algorithms/lib/libalgorithms.a

all: src/GraphGenerator.cpp src/main.cpp $(STRUCTS_FLIB) $(ALGS_FLIB)
	g++ -Wall -I./include -I../structures/include -I../algorithms/include src/GraphGenerator.cpp src/main.cpp -o GraphGenerator -L../structures/lib -lstructures -L../algorithms/lib -lalgorithms

$(STRUCTS_FLIB):
	make -C ../structures

$(ALGS_FLIB):
	make -C ../algorithms

clean:
	rm -f GraphGenerator