#include "FlightPathGraph.h"

void FlightPathGraph::readFile(){
	flightPathFile.open("flight.txt");
	string node, connection;

	if (flightPathFile.is_open()) {
		while (getline(flightPathFile, fileInputLine)) {

			//get starting city name
			if (fileInputLine.find("From:") == 0) {
				node = fileInputLine.substr(7, fileInputLine.length());
			}

			//get first connection city, and add to map
			else if (fileInputLine.find("To  :") == 0) {
				connection = fileInputLine.substr(7, fileInputLine.length());
				addEdge(node, connection);
			}

			//get subsequent connection cities, and add to map
			else {
				connection = fileInputLine.substr(7, fileInputLine.length());
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


//Prints out a city and all its connections
void FlightPathGraph::printGraph(){
	//Iterate over our dictionary
	for (auto iter = edges.begin(); iter !=  edges.end(); ++iter){
        cout << "[" << iter->first << "]" << endl;
		//Get a reference to the vector
		vector<string> ls = iter->second;

		//Print out the vector
		for(int i = 0; i < ls.size(); i++){
			cout << "\t" << ls[i] << endl;
		}
    }
}
