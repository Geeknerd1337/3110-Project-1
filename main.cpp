#include <iostream>
#include "FlightPathGraph.h"
using namespace std;

int main() {
    //Declare our given flight graph
    FlightPathGraph graph;
    //city names to use as parametres
    string city1, city2, city3, city4;
    //menu choice and max connections for option 1
    int menuOpt = 0, connec = 0;

    //read in file to create graph
    graph.readFile();

    cout << "Enter city names in the format of 'Cityname, Countryname' \nFor example: 'Rome, Italy'\n";

    //loop until quit choice is chosen
    do {
        //display menu
        cout << "\nType a number to select a kind of route\n"
            << "1. Find the shortest route from one city to another with a max number of connections\n"
            << "2. Find the shortest path from one city to another that passes through two other cities\n"
            << "3. Find the shortest route leaving a city back to the same city\n"
            << "4. Find the closest meeting place between three cities\n"
            << "5. Quit the program\n";

        //get menu choice and eat \n
        cin >> menuOpt;
        cin.ignore();

        //get proper input for each routeSearch and call it
        switch (menuOpt) {
        case 1:
            cout << "Enter starting city: ";
            getline(cin, city1);
            cout << "Enter destination: ";
            getline(cin, city2);
            cout << "Enter maximum number of connections: ";
            cin >> connec;
            cout << endl;

            graph.routeSearch1(city1, city2, connec);
            break;
        case 2:
            cout << "Enter starting city: ";
            getline(cin, city1);
            cout << "Enter destination: ";
            getline(cin, city4);
            cout << "Enter a city to stop in: ";
            getline(cin, city2);
            cout << "Enter a city to stop in: ";
            getline(cin, city3);
            cout << endl;

            graph.routeSearch2(city1, city3, city2, city4);
            break;
        case 3:
            cout << "Enter a city: ";
            getline(cin, city1);
            cout << endl;
            
            graph.routeSearch3(city1);
            break;
        case 4:
            cout << "Enter a city to meet from: ";
            getline(cin, city1);
            cout << "Enter a city to meet from: ";
            getline(cin, city2);
            cout << "Enter a city to meet from: ";
            getline(cin, city3);
            cout << endl;

            graph.routeSearch4(city1, city2, city3);
            break;
        default:
            break;
        }

    } while (menuOpt != 5);


    return 0;
}
