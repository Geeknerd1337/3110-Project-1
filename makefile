
project: main.cpp FlightPathGraph.cpp
	g++ -g -Wall -o project main.cpp FlightPathGraph.cpp -I.

clean:
	$(RM) project
