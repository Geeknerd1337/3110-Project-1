#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>

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
	
	map<string, vector<string> > edges;

};

