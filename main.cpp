#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //Read in the local file
    graph.readFile();

    if(graph.breadthFirstSearch("Zurich, Switzerland","Lagos, Nigeria")){
        cout << "Found Path Between Two Cities" << endl;
        graph.printPath();
    }else{
        cout << "*sad program noise*" << endl;
    }

    return 0;
}