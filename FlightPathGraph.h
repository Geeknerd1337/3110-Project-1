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
	//string to holde each line of file and file object
	string fileInputLine;
	ifstream flightPathFile;
	//vector to hold cities that were visited in processPath method
	vector<string> visitedInProcess;
public:

	//read input file to make graph
	void readFile();

	//add an edge to the edges map
	void addEdge(string node, string connection);

	//print the edges map
	void printGraph();

	//BFS
	bool breadthFirstSearch(string start, string end);

	//display a path
	void printPath();

	//holds nodes and their parents
	map<string, vector<string>> parents;

	//holds a path of cities
	vector<string> path;

	//process a path from BFS
	void processPath(string start, string end, bool addEndToPath);

	//problem 1
	void routeSearch1(string start, string end, int num);
	//problem 2
	void routeSearch2(string start, string visit1, string visit2, string end);
	//problem 3
	void routeSearch3(string city);
	//problem 4
	void routeSearch4(string city1, string city2, string city3);
	
	//display parents map
	void printParents();

	//represents cities graph
	map<string, vector<string> > edges;

};
