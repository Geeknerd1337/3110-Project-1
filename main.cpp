#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();
    
    graph.routeSearch3("Bogot, Colombia");
    


    return 0;
}
