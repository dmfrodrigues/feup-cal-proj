all: generator.cpp ../map/processed/AMP.points
	g++ -Wall -I../include -I../structures/include -I../utils/include generator.cpp ../src/Client.cpp ../structures/src/point.cpp ../utils/src/encoded_string.cpp ../structures/src/coord.cpp -o generator

../map/processed/AMP.points: 
	make -C ../map

clean:
	rm -f generator