PROG=./map_process
CC=g++
IDIR_RAPIDXML=-I./rapidxml
IDIR=-I../include

PROCESSED_DIR=./processed

all: processed/AMP.nodes

processed/AMP.nodes: map_process.cpp original/map.xml | $(PROCESSED_DIR)
	$(CC) $(IDIR_RAPIDXML) $(IDIR) map_process.cpp -o $(PROG)
	$(PROG) $(PROCESSED_DIR)/AMP < original/map.xml

$(PROCESSED_DIR):
	mkdir -p $@

clean:
	rm -rf $(PROCESSED_DIR)
	rm $(PROG)
