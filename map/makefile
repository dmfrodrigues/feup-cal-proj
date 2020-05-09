CC=g++
IDIR_RAPIDXML=-I./rapidxml
IDIR=-I../include

all: map_process.cpp
	$(CC) $(IDIR_RAPIDXML) $(IDIR) map_process.cpp -o map_process
	./map_process processed/AMP < original/map.xml
