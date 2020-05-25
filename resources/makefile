all: src/input_generator.cpp ../map/processed/AMP.points main.cpp
	g++ -Wall -I./include -I../include -I../structures/include -I../utils/include src/input_generator.cpp main.cpp ../src/Client.cpp ../structures/src/point.cpp ../utils/src/encoded_string.cpp ../structures/src/coord.cpp -o input_generator

../map/processed/AMP.points: 
	make -C ../map

clean:
	rm -f input_generator
	rm -f generator