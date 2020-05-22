PROG   =main
all: $(PROG) data

FORCE:

CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
TDIR   =./test
TEXE   =$(ODIR)/test

GV_LIB =graphviewer
GV_DIR =./GraphViewer
GV_IDIR=$(GV_DIR)/cpp
GV_LDIR=$(GV_DIR)/lib
GV_FLIB=$(GV_LDIR)/lib$(GV_LIB).a
$(GV_FLIB): FORCE
	make -C $(GV_DIR)

UTILS_LIB =utils
UTILS_DIR =./utils
UTILS_IDIR=$(UTILS_DIR)/include
UTILS_LDIR=$(UTILS_DIR)/lib
UTILS_FLIB=$(UTILS_LDIR)/lib$(UTILS_LIB).a
$(UTILS_FLIB): FORCE
	make -C $(UTILS_DIR)

STRUCTS_LIB =structures
STRUCTS_DIR =./structures
STRUCTS_IDIR=$(STRUCTS_DIR)/include
STRUCTS_LDIR=$(STRUCTS_DIR)/lib
STRUCTS_FLIB=$(STRUCTS_LDIR)/lib$(STRUCTS_LIB).a
$(STRUCTS_FLIB): FORCE
	make -C $(STRUCTS_DIR)

ALGS_LIB =algorithms
ALGS_DIR =./algorithms
ALGS_IDIR=$(ALGS_DIR)/include
ALGS_LDIR=$(ALGS_DIR)/lib
ALGS_FLIB=$(ALGS_LDIR)/lib$(ALGS_LIB).a
$(ALGS_FLIB): FORCE
	make -C $(ALGS_DIR)

IFLAGS =-I$(IDIR) -I$(GV_IDIR) -I$(UTILS_IDIR) -I$(STRUCTS_IDIR) -I$(ALGS_IDIR)

LFLAGS =-L$(GV_LDIR)      -l$(GV_LIB) \
		-L$(ALGS_LDIR)    -l$(ALGS_LIB) \
		-L$(STRUCTS_LDIR) -l$(STRUCTS_LIB) \
		-L$(UTILS_LDIR)   -l$(UTILS_LIB)

LREQUIREMENTS=$(GV_FLIB) $(ALGS_FLIB) $(STRUCTS_FLIB) $(UTILS_FLIB)

CFLAGS_OPTIMIZE=-Ofast -fno-signed-zeros -fno-trapping-math -frename-registers -funroll-loops
CFLAGS_PARANOID=-pthread -g -O -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport  -Winit-self  -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings# -Weffc++ -Wpadded 
#CFLAGS =-Wall -pthread -g $(CFLAGS_OPTIMIZE) $(IFLAGS)
CFLAGS=$(IFLAGS) $(CFLAGS_PARANOID) $(CFLAGS_OPTIMIZE)

data: FORCE
	make -C map

O_FILES=$(ODIR)/MapGraph.o $(ODIR)/MapViewer.o#$(ODIR)/Client.o $(ODIR)/Van.o

$(PROG): $(O_FILES) $(SDIR)/main.cpp $(LREQUIREMENTS)
	$(CC) $(CFLAGS) $(O_FILES) $(SDIR)/main.cpp -o $(PROG) $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR)
	rm -f $(PROG)
	make -C structures clean
	make -C algorithms clean

cleanall:
	make clean
	make -C utils clean
	make -C map clean
	make -C GraphViewer clean

test: $(TEXE)
	$(TEXE)

$(TEXE): $(PROG) $(TDIR)/test.cpp $(O_FILES)
	$(CC) $(CFLAGS) -I$(TDIR)/Catch2/single_include/catch2 $(O_FILES) $(TDIR)/test.cpp -o $(TEXE) $(LFLAGS)
