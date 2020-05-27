LIB	    =algorithms
SDIR	=./src
IDIR	=./include
ODIR   	=./obj
LDIR    =./lib
FLIB	=$(LDIR)/lib$(LIB).a #Library file
#TDIR   	=./test
#TFILE	=test
#TAPP   	=$(ODIR)/test
#ACUTEST =../acutest/include

UTILS_LIB =utils
UTILS_DIR =../$(UTILS_LIB)
UTILS_IDIR=$(UTILS_DIR)/include
# UTILS_LDIR=$(UTILS_DIR)/lib
# UTILS_FLIB=$(UTILS_LDIR)/lib$(UTILS_LIB).a

STRUCTS_LIB =structures
STRUCTS_DIR =../$(STRUCTS_LIB)
STRUCTS_IDIR=$(STRUCTS_DIR)/include
# STRUCTS_LDIR=$(STRUCTS_DIR)/lib
# STRUCTS_FLIB=$(STRUCTS_LDIR)/lib$(STRUCTS_LIB).a

CC     =g++

IFLAGS =-I$(IDIR) -I$(UTILS_IDIR) -I$(STRUCTS_IDIR)

CFLAGS_OPTIMIZE=-Ofast -fno-signed-zeros -fno-trapping-math -frename-registers -funroll-loops
CFLAGS_PARANOID=-pthread -g -O -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport  -Winit-self  -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings -Wpadded #-Weffc++  
#CFLAGS =-Wall -pthread -g $(CFLAGS_OPTIMIZE) $(IFLAGS)
CFLAGS=$(IFLAGS) $(CFLAGS_PARANOID) $(CFLAGS_OPTIMIZE)

O_FILES=$(ODIR)/Astar.o $(ODIR)/ClosestPoint.o $(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/FloydWarshall.o $(ODIR)/Kosaraju.o $(ODIR)/KosarajuV.o $(ODIR)/SCCnode.o \
	$(ODIR)/ShortestPath.o $(ODIR)/ShortestPathAll.o $(ODIR)/ShortestPathOneMany.o $(ODIR)/Tarjan.o $(ODIR)/VStripes.o $(ODIR)/NearestNeighbour.o $(ODIR)/Reachability.o \
	$(ODIR)/TravellingSalesman.o $(ODIR)/HeldKarp.o

all: $(FLIB)

$(FLIB):   $(O_FILES) | $(LDIR)
	rm -f $(FLIB)
	ar rvs $(FLIB) $(O_FILES)

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(ODIR):
	mkdir -p $@

$(LDIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)

# test: ./$(TAPP)
# 	./$(TAPP)

# $(TAPP): $(TSRC) $(LIB)
# 	$(CC) $(CFLAGS) -I$(ACUTEST) -c $(TDIR)/$(TFILE).c -o $(ODIR)/$(TFILE).o
# 	$(CC) $(ODIR)/$(TFILE).o -o $(TAPP) $(LFLAGS)

# testmem: ./$(TAPP)
# 	valgrind --leak-check=yes $(TAPP)