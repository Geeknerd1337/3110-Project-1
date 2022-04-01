#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

class FlightPathGraph
{
private:
	string fileInputLine;
	ifstream flightPathFile;
	map<string, list<string> > edges;


public:

	void readFile();

	void addEdge(string node, string connection);


};

