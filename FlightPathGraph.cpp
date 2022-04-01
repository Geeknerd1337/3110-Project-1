#include "FlightPathGraph.h"

void FlightPathGraph::readFile(){
	flightPathFile.open("flight.txt");
	string node, connection;

	if (flightPathFile.is_open()) {
		while (getline(flightPathFile, fileInputLine)) {

			//get starting city name
			if (fileInputLine.find("From:") == 0) {
				node = fileInputLine.substr(6, fileInputLine.length());
			}

			//get first connection city, and add to map
			else if (fileInputLine.find("To:") == 0) {
				connection = fileInputLine.substr(4, fileInputLine.length());
				addEdge(node, connection);
			}

			//get subsequent connection cities, and add to map
			else {
				connection = fileInputLine;
				addEdge(node, connection);
			}
		}
	}

	flightPathFile.close();
}

//push connection to node's list
void FlightPathGraph::addEdge(string node, string connection) {
	edges[node].push_back(connection);
}
