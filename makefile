PROG   =main

IFLAGS =$(IDIR)

CC     =g++

SDIR   =./src
IDIR   =-I./include
ODIR   =./obj
TDIR   =./test
TEXE   =test

CFLAGS =-Wall -g $(IFLAGS) #-O3

all: makefolders $(PROG)

clean:
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

O_FILES=$(ODIR)/DFS.o $(ODIR)/Dijkstra.o $(ODIR)/DUGraph.o $(ODIR)/DWGraph.o $(ODIR)/KosarajuV.o

makefolders:
	mkdir -p $(ODIR)

$(PROG):  $(O_FILES)
	echo Compiling
	# $(CC) $(ODIR)/simpledu.o $(ODIR)/simpledu_args.o $(ODIR)/simpledu_envp.o $(ODIR)/simpledu_stat.o $(ODIR)/simpledu_log.o $(ODIR)/simpledu_time.o $(ODIR)/simpledu_iterate.o -o simpledu

$(ODIR)/%.o:          $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
