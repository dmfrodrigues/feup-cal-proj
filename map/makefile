PROCESSED_DIR=./processed
all: $(PROCESSED_DIR)/AMP.nodes

PROG=./map_process
CC=g++
IDIR_RAPIDXML=./rapidxml

UTILS_LIB =utils
UTILS_DIR =../utils
UTILS_IDIR=$(UTILS_DIR)/include
UTILS_LDIR=$(UTILS_DIR)/lib
UTILS_FLIB=$(UTILS_LDIR)/lib$(UTILS_LIB).a
$(UTILS_FLIB):
	make -C $(UTILS_DIR)

STRUCTS_LIB =structures
STRUCTS_DIR =../structures
STRUCTS_IDIR=$(STRUCTS_DIR)/include
STRUCTS_LDIR=$(STRUCTS_DIR)/lib
STRUCTS_FLIB=$(STRUCTS_LDIR)/lib$(STRUCTS_LIB).a
$(STRUCTS_FLIB):
	make -C $(STRUCTS_DIR)

IFLAGS =-I$(IDIR_RAPIDXML) -I$(UTILS_IDIR) -I$(STRUCTS_IDIR)
LFLAGS =-L$(UTILS_LDIR) -l$(UTILS_LIB) \
	-L$(STRUCTS_LDIR) -l$(STRUCTS_LIB)

CFLAGS_OPTIMIZE=-Ofast -fno-signed-zeros -fno-trapping-math -frename-registers -funroll-loops
CFLAGS_PARANOID=-pthread -g -O -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport  -Winit-self  -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings# -Weffc++ -Wpadded 
#CFLAGS =-Wall -pthread -g $(CFLAGS_OPTIMIZE) $(IFLAGS)
CFLAGS=$(IFLAGS) $(CFLAGS_PARANOID) $(CFLAGS_OPTIMIZE)

$(PROG): map_process.cpp $(UTILS_FLIB) $(STRUCTS_FLIB)
	$(CC) $(CFLAGS) map_process.cpp $(LFLAGS) -o $(PROG)

$(PROCESSED_DIR)/AMP.nodes: $(PROG) original/map.xml | $(PROCESSED_DIR)
	# $(PROG) $(PROCESSED_DIR)/AMP < original/map.xml

$(PROCESSED_DIR):
	mkdir -p $@

clean:
	rm -rf $(PROCESSED_DIR)
	rm -f $(PROG)
