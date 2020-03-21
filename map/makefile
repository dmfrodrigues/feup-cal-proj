CC=g++
INCLUDE=-I./rapidxml/

all: map_process.cpp
	$(CC) $(INCLUDE) map_process.cpp -o map_process
	./map_process processed/AMP < original/map.xml
