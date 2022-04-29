#include "FlightPathGraph.h"

//A nice wrapper for std which allows us to check the contents of a container for a specified value
//This solution was thankfully provided by the following link and is really cool:
//https://stackoverflow.com/questions/24139428/check-if-element-is-in-the-list-contains
namespace std
{
	template<class _container,
		class _Ty> inline
		bool contains(_container _C, const _Ty& _Val)
	{
		return std::find(_C.begin(), _C.end(), _Val) != _C.end();
	}
};

//Read in the "flight.txt" file and turn it into a graph by adding nodes and connections to the edges map
void FlightPathGraph::readFile() {
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
void FlightPathGraph::printGraph() {
	//Iterate over our dictionary
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		cout << "[" << iter->first << "]" << endl;
		//Get a reference to the vector
		vector<string> ls = iter->second;

		//Print out the vector
		for (int i = 0; i < ls.size(); i++) {
			cout << "\t" << ls[i] << endl;
		}
	}
}

//Traces up through a path to print out the nodes it visisted
void FlightPathGraph::printPath() {

	//Iterate over the path and print it
	for (int i = 0; i < path.size(); i++) {
		cout << path[i];
		if (i + 1 < path.size()) {
			cout << " -> ";
		}
	}
	cout << endl;
}


//displays the parents map
void FlightPathGraph::printParents() {

	//Iterate over the parents and print them
	
	//string, vector version
	for (auto iter = parents.begin(); iter != parents.end(); ++iter) {
		cout << "[" << iter->first << "]" << endl;
		//Get a reference to the vector
		vector<string> ls = iter->second;

		//Print out the vector
		for (int i = 0; i < ls.size(); i++) {
			cout << "\t" << ls[i] << endl;
		}
	}


}

//This processes a path by iterating upwards through the parents of nodes
//This is kind of messy, but that's okay :)
void FlightPathGraph::processPath(string start, string end, bool addEndToPath) {
	string child = end;
	path.clear();
	//keep track of which cities have been visitied in this function
	visitedInProcess.clear();
	if (addEndToPath) {
		path.push_back(end);
	}
	int i = 0;

	//this was for a more complicated idea of storing an index for each child
	//vector<int> indexes(parents.size(), 0);

	while (child.compare(start) != 0) {
		//push city to visited vector
		visitedInProcess.push_back(child);

		//if i isn't out of range, use it as an index
		if (i < parents[child].size()) {
			path.push_back(parents[child][i]);
			//cout << parents[child][i] << endl;
			child = parents[child][i];
		}
		//if it is, just use size as an index
		else {
			path.push_back(parents[child][parents[child].size()]);
			//cout << parents[child][parents[child].size()-1] << endl;
			child = parents[child][parents[child].size() - 1];
		}

		//if we encounter a city we've been to, gtfo and start again with a higher index
		if (contains(visitedInProcess, child))
		{
			i++;
			child = end;
			path.clear();
			if (addEndToPath) {
				path.push_back(end);
			}
		}

	}

	reverse(path.begin(), path.end());
}



//Question 1 from the project
//simple BFS and then use process path, then see if path size is desired length
void FlightPathGraph::routeSearch1(string start, string end, int num) {
	//Use BFS to find the shortest path between the start and the end
	if (breadthFirstSearch(start, end) == true) {
		//Process the path to get a vector
		processPath(start, end, true);
		//Check the length of that path to validate that it is of the length desired
		if (path.size() > num) {
			printf("A path of the size you requested does not exist.\n");
		}
		else {
			printf("We have found a path of the desired length or shorter:\n");
			printPath();
			cout << endl;
		}
	}
	else {
		printf("A path does not exist between the two cities you selected\n\n");
	}
}

//Question 3 of project
//Use BFS and process path on all of city's adjacent cities
void FlightPathGraph::routeSearch3(string city) {

	vector<string> citiesToVisit = edges[city];
	int maxDistance = INT_MAX;
	int selectedIndex = -1;

	for (int i = 0; i < citiesToVisit.size(); i++) {
		string cityConnection = citiesToVisit[i];
		if (breadthFirstSearch(cityConnection, city)) {
			processPath(cityConnection, city, true);

			if (path.size() < maxDistance) {
				maxDistance = path.size();
				selectedIndex = i;
			}
		}
	}

	//Then literally just run this again one last time to get the correct original path
	//TODO: Probably just faster to cache the best path as a vector instead of doing another search but 
	//this is slightly more convienent
	string cityConnection = citiesToVisit[selectedIndex];
	if (breadthFirstSearch(cityConnection, city)) {
		processPath(cityConnection, city, true);
		cout << city << " -> ";
		printPath();
	}
	else {
		printf("A path does not exist between the two cities you selected\n\n");
	}
}

//Question 4 of the project
//use BFS to on every city to see which has the best paths to the desired cities
void FlightPathGraph::routeSearch4(string city1, string city2, string city3) {
	//Set a maximum distance
	int dist = INT_MAX;
	string finalDest = "";
	path.clear();

	//This is *incredibly* inefficient but we're gonna iterate over every node in the graph
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		//A current distance variable 
		int curDistance = 0;

		string city = iter->first;
		//If the current city we're looking at
		if (city.compare(city1) == 0 || city.compare(city2) == 0 || city.compare(city3) == 0) {
			continue;
		}

		//See if we get a path to city 1
		if (breadthFirstSearch(city, city1)) {
			processPath(city, city1, true);
			curDistance += path.size();
		}
		else {
			//if we don't find a path, just stop looking
			continue;
		}

		//See if we can get a path to city 2
		if (breadthFirstSearch(city, city2)) {
			processPath(city, city2, true);
			curDistance += path.size();
		}
		else {
			continue;
		}

		//See if we can get a path to city 3
		if (breadthFirstSearch(city, city3)) {
			processPath(city, city3, true);
			curDistance += path.size();
		}
		else {
			continue;
		}

		//If we made it this far, there is a path to all 3 cities, so now we check to see if this distance is the smallest
		if (curDistance < dist) {
			dist = curDistance;
			finalDest = city;
		}
	}

	//Finally, if our finalDest isn't equal to "", then we can print the paths, otherwise, there is no path.
	if (finalDest.compare("") != 0) {
		printf("Here are your paths for a minimum distance between these cities:\n");
		breadthFirstSearch(city1, finalDest);
		processPath(city1, finalDest, true);
		printPath();

		breadthFirstSearch(city2, finalDest);
		processPath(city2, finalDest, true);
		printPath();

		breadthFirstSearch(city3, finalDest);
		processPath(city3, finalDest, true);
		printPath();

	}
	else {
		printf("There exists no path between these 3 cities.\n\n");
	}
}

//Question 2 of the project
//use BFS to figure out if A -> B -> C -> D or A -> C -> B -> D is a better path
void FlightPathGraph::routeSearch2(string start, string visit1, string visit2, string end) {
	int distance1 = 0;
	int distance2 = 0;
	vector<string> path1;
	vector<string> path2;

	//Our first case, which performs several breadth first searches over the given subgraph:
	//A -> B -> C -> D
	if (breadthFirstSearch(start, visit1)) {
		processPath(start, visit1, false);
		distance1 += path.size();
		path1.insert(path1.end(), path.begin(), path.end());

		if (breadthFirstSearch(visit1, visit2)) {
			processPath(visit1, visit2, false);
			distance1 += path.size();
			path1.insert(path1.end(), path.begin(), path.end());

			if (breadthFirstSearch(visit2, end)) {
				processPath(visit2, end, true);
				distance1 += path.size();
				path1.insert(path1.end(), path.begin(), path.end());

			}
			else {
				distance1 = -1;
			}
		}
		else {
			distance1 = -1;
		}
	}
	else {
		distance1 = -1;
	}

	//Our first case, which performs several breadth first searches over the given subgraph:
	//A -> C -> B -> D
	if (breadthFirstSearch(start, visit2)) {
		processPath(start, visit2, false);
		distance2 += path.size();
		path2.insert(path2.end(), path.begin(), path.end());

		if (breadthFirstSearch(visit2, visit1)) {
			processPath(visit2, visit1, false);
			distance2 += path.size();
			path2.insert(path2.end(), path.begin(), path.end());
			if (breadthFirstSearch(visit1, end)) {
				processPath(visit1, end, true);
				distance2 += path.size();
				path2.insert(path2.end(), path.begin(), path.end());
			}
			else {
				distance2 = -1;
			}
		}
		else {
			distance2 = -1;
		}
	}
	else {
		distance2 = -1;
	}



	if (distance1 > distance2) {
		path = path2;
		printPath();
	}
	else if (distance2 > distance1) {
		path = path1;
		printPath();
	}
	else if (distance1 == distance2 && distance1 != -1 && distance2 != -1) {
		printf("The distances between the following paths are equal:\n");
		path = path1;
		printPath();
		path = path2;
		printPath();
	}

	if (distance1 == -1 && distance2 == -1) {
		printf("There is no path which takes you to the two desired cities\n\n");
	}

}

//Implementation of a breadth-first search algorithm
bool FlightPathGraph::breadthFirstSearch(string start, string end) {
	//Clear our path
	parents.clear();

	//A list of strings of nodes that need to be scanned as per the BFS algorithm
	list<string> openSet;

	//A list of strings representing our already visisted nodes
	list<string> closedSet;

	//Our origin node doesn't need to be visited so we can add it to the closed set
	closedSet.push_back(start);
	//We need to add our source to the open set since we need to scan it first
	openSet.push_back(start);

	//Run this while our open set is not empty
	while (!openSet.empty()) {
		//Get the node we're gonna scan
		string node = openSet.front();
		//Remove that node from the open set
		openSet.pop_front();
		//Now we're gonna iterate over our 'connections' in that portion of the graph
		for (int i = 0; i < edges[node].size(); i++) {
			//In theory this gets the connection at the given node
			string child = edges[node][i];
			//We check to see if this is not in our closed set, and if not, we add it to our open set to be scanned
			if (!contains(openSet, child)) {
				//Add it to our open set
				openSet.push_back(child);

				//What this is basically doing is giving an entry in the map where you will give a given destination node and be able to trace back to its parent
				//parents[child] = node;
				if (!contains(parents[child], node)) {
					parents[child].push_back(node);
				}

				//Now we check to see if we've reached our destination, and if so, return true
				if (child.compare(end) == 0) {
					return true;
				}
			}
		}
	}

	return false;
}
