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

CFLAGS =-Wall -g $(IFLAGS)#-O3

all: data $(PROG)

data:
	make -C map

O_FILES=$(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/DUGraph.o $(ODIR)/DWGraph.o $(ODIR)/Kosaraju.o $(ODIR)/KosarajuV.o $(ODIR)/MapGraph.o

$(PROG): $(O_FILES) $(LIB_GV) $(ODIR)/main.o
	$(CC) $(O_FILES) $(ODIR)/main.o -o $(PROG) -L$(LDIR_GV) -lgraphviewer

$(LIB_GV):
	make -C GraphViewer

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	make -C map clean
	rm -rf $(ODIR)
	rm -f $(ODIR)/$(TEXE)
	rm -f $(PROG)

test: $(PROG) $(TDIR)/test.cpp $(O_FILES)
	$(CC) $(CFLAGS) -I$(TDIR)/Catch2/single_include/catch2 $(O_FILES) $(TDIR)/test.cpp -o $(TEXE) -L$(LDIR_GV) -lgraphviewer
	$(TEXE)
