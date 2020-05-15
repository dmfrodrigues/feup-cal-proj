PROG   =main

CC     =g++

SDIR   =./src
IDIR   =-I./include
ODIR   =./obj
TDIR   =./test
TEXE   =$(ODIR)/test

GVDIR=./GraphViewer
IDIR_GV=-I$(GVDIR)/cpp
LDIR_GV=$(GVDIR)/lib
LIB_GV=$(LDIR_GV)/libgraphviewer.a

IFLAGS =$(IDIR) $(IDIR_GV)

CFLAGS_PARANOID=-g -O -Wall -pedantic -Wunused-result  \
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
    -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 \
    -Wformat-nonliteral -Wformat-security  \
    -Wformat-y2k \
    -Wimport  -Winit-self  -Winline \
    -Winvalid-pch   \
    -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute   \
    -Wmissing-include-dirs -Wmissing-noreturn \
    -Wpacked -Wparentheses  -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused \
    -Wunused-function  -Wunused-label  -Wunused-parameter \
    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings #-Werror -Weffc++ -Waggregate-return -Wpadded 
#CFLAGS =-Wall -g $(IFLAGS)#-O3
CFLAGS=$(CFLAGS_PARANOID) $(IFLAGS)

all: data $(PROG)

data:
	make -C map

O_FILES=$(ODIR)/Astar.o $(ODIR)/coord.o $(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/DUGraph.o $(ODIR)/DWGraph.o $(ODIR)/Kosaraju.o $(ODIR)/KosarajuV.o $(ODIR)/MapGraph.o $(ODIR)/MapViewer.o $(ODIR)/SCCnode.o $(ODIR)/ShortestPath.o $(ODIR)/ShortestPathAll.o $(ODIR)/ShortestPathOneMany.o

$(PROG): $(O_FILES) $(LIB_GV) $(ODIR)/main.o
	$(CC) $(O_FILES) $(ODIR)/main.o -o $(PROG) -L$(LDIR_GV) -lgraphviewer

$(LIB_GV):
	make -C GraphViewer

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	#make -C map clean
	rm -rf $(ODIR)
	rm -f $(ODIR)/$(TEXE)
	rm -f $(PROG)

test: $(PROG) $(TDIR)/test.cpp $(O_FILES)
	$(CC) $(CFLAGS) -I$(TDIR)/Catch2/single_include/catch2 $(O_FILES) $(TDIR)/test.cpp -o $(TEXE) -L$(LDIR_GV) -lgraphviewer
	$(TEXE)
