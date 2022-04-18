#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();
    
    graph.routeSearch4("Bogot, Colombia","Tel Aviv, Israel","Lusaka, Zambia");
   

    return 0;
}
