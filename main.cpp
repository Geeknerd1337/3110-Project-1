#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();

    //graph.routeSearch2("Winston-Salem, United States","Tel Aviv, Israel","Warsaw, Poland","Brisbane, Australia");
    graph.breadthFirstSearch("Warsaw, Poland", "Tel Aviv, Israel");
    //graph.processPath("Tel Aviv, Israel", "Brisbane, Australia");
    //graph.printPath();
    graph.printParents();

    return 0;
}