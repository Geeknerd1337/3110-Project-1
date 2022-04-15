#include "FlightPathGraph.h"

//A nice wrapper for std which allows us to check the contents of a container for a specified value
//This solution was thankfully provided by the following link and is really cool:
//https://stackoverflow.com/questions/24139428/check-if-element-is-in-the-list-contains
namespace std
{
    template<class _container,
        class _Ty> inline
        bool contains(_container _C, const _Ty& _Val)
        {return std::find(_C.begin(), _C.end(), _Val) != _C.end(); }
};

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

//Implementation of a breadth-first search algorithm
bool FlightPathGraph::breadthFirstSearch(string start, string end){

	//A list of strings of nodes that need to be scanned as per the BFS algorithm
	list<string> openSet;

	//A list of strings representing our already visisted nodes
	list<string> closedSet;

	//Our origin node doesn't need to be visited so we can add it to the closed set
	closedSet.push_back(start);
	//We need to add our source to the open set since we need to scan it first
	openSet.push_back(start);

	//Run this while our open set is not empty
	while(!openSet.empty()){
		//Get the node we're gonna scan
		string node = openSet.front();
		//Remove that node from the open set
		openSet.pop_front();
		//Now we're gonna iterate over our 'connections' in that portion of the graph
		for(int i = 0; i < edges[node].size(); i++){
			//In theory this gets the connection at the given node
			string s = edges[node][i];
			//We check to see if this is not in our closed set, and if not, we add it to our open set to be scanned
			if(!contains(openSet,s)){
				//Add it to our open set
				openSet.push_back(s);

				//What this is basically doing is giving an entry in the map where you will give a given destination node and be able to trace back to its parent
				path[s] = node;

				//Now we check to see if we've reached our destination, and if so, return true
				if(s.compare(end) == 0){
					return true;
				}
			}
		}
	}

	return false;
}


