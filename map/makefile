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

$(PROG): map_process.cpp $(UTILS_FLIB) $(STRUCTS_FLIB)
	$(CC) $(IFLAGS) map_process.cpp $(LFLAGS) -o $(PROG)

$(PROCESSED_DIR)/AMP.nodes: $(PROG) original/map.xml | $(PROCESSED_DIR)
	$(PROG) $(PROCESSED_DIR)/AMP < original/map.xml

$(PROCESSED_DIR):
	mkdir -p $@

clean:
	rm -rf $(PROCESSED_DIR)
	rm -f $(PROG)
