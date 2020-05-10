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

test: all
	@echo Current directory: $(PWD)
	# $(CC) $(CFLAGS) -c -I./acutest/include $(TDIR)/tests.c -o $(ODIR)/tests.o
	# $(CC) $(ODIR)/tests.o $(ODIR)/simpledu_args.o $(ODIR)/simpledu_envp.o $(ODIR)/simpledu_stat.o $(ODIR)/simpledu_log.o $(ODIR)/simpledu_time.o $(ODIR)/simpledu_iterate.o -o $(ODIR)/$(TEXE)
	# $(ODIR)/$(TEXE)
	# chmod u+x $(TDIR)/*.sh
	# $(TDIR)/test_compare_du.sh

# testmem: all
# 	valgrind --leak-check=yes $(ODIR)/$(TEXE)

O_FILES=$(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/DUGraph.o $(ODIR)/DWGraph.o $(ODIR)/KosarajuV.o $(ODIR)/main.o $(ODIR)/MapGraph.o

$(PROG): $(O_FILES) $(LIB_GV)
	$(CC) $(O_FILES) -o $(PROG) -L$(LDIR_GV) -lgraphviewer

$(LIB_GV):
	make -C GraphViewer

$(ODIR)/%.o: $(SDIR)/%.cpp $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)
