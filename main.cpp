#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();

    //Print the map for testing purposes
    graph.printMap();    

    return 0;
}