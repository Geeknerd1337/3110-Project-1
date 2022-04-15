#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();

    graph.routeSearch2("Winston-Salem, United States","Tel Aviv, Israel","Warsaw, Poland","Brisbane, Australia");
   

    return 0;
}
