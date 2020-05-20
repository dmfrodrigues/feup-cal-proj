PROG=./map_process
CC=g++
IDIR_RAPIDXML=-I./rapidxml
IDIR=-I../include

PROCESSED_DIR=./processed

all: processed/AMP.nodes

$(PROG): map_process.cpp ../obj/coord.o
	$(CC) $(IDIR_RAPIDXML) $(IDIR) ../obj/coord.o map_process.cpp -o $(PROG)

processed/AMP.nodes: $(PROG) original/map.xml | $(PROCESSED_DIR)
	$(PROG) $(PROCESSED_DIR)/AMP < original/map.xml

$(PROCESSED_DIR):
	mkdir -p $@

../obj/coord.o:
	make -C .. ./obj/coord.o

clean:
	rm -rf $(PROCESSED_DIR)
	rm $(PROG)
