#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class FlightPathGraph
{
private:
	string fileInputLine;
	ifstream flightPathFile;

	vector<string> visitedInProcess;
public:

	void readFile();

	void addEdge(string node, string connection);

	void printGraph();

	bool breadthFirstSearch(string start, string end);

	void printPath();

	//map<string, string> parents;
	map<string, vector<string>> parents;

	vector<string> path;

	void processPath(string start, string end, bool addEndToPath);

	void routeSearch1(string start, string end, int num);

	void routeSearch2(string start, string visit1, string visit2, string end);

	void routeSearch4(string city1, string city2,string city3);

	void printParents();

	map<string, vector<string> > edges;

};
