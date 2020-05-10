PROG   =main

CC     =g++

SDIR   =./src
IDIR   =-I./include
ODIR   =./obj
TDIR   =./test
TEXE   =test

GVDIR=./GraphViewer
IDIR_GV=-I$(GVDIR)/cpp
LDIR_GV=$(GVDIR)/lib
LIB_GV=$(LDIR_GV)/libgraphviewer.a

IFLAGS =$(IDIR) $(IDIR_GV)

CFLAGS =-Wall -g $(IFLAGS)#-O3

all: $(PROG)

clean:
	#make -C GraphViewer clean
	rm -rf $(ODIR)
	rm -f $(ODIR)/$(TEXE)
	rm -f $(PROG)

$(TEXE): all
	$(CC) -ICatch2/include $(TDIR)/test.cpp -o $(ODIR)/test #-L$(LDIR_GV) -lgraphviewer

test: $(TEXE)
	$(TEXE)

# testmem: all
# 	valgrind --leak-check=yes $(ODIR)/$(TEXE)

O_FILES=$(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/DUGraph.o $(ODIR)/DWGraph.o $(ODIR)/KosarajuV.o $(ODIR)/MapGraph.o

$(PROG): $(O_FILES) $(LIB_GV) $(ODIR)/main.o
	$(CC) $(O_FILES) $(ODIR)/main.o -o $(PROG) -L$(LDIR_GV) -lgraphviewer

$(LIB_GV):
	make -C GraphViewer

$(ODIR)/%.o: $(SDIR)/%.cpp $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)
