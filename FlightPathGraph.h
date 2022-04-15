#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class FlightPathGraph
{
private:
	string fileInputLine;
	ifstream flightPathFile;
public:

	void readFile();

	void addEdge(string node, string connection);

	void printGraph();

	bool breadthFirstSearch(string start, string end);

	map<string, string> path;
	
	map<string, vector<string> > edges;

};

