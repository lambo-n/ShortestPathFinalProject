#include <iostream>
#include <cstdlib>
#include <map>
#include "Headers/map.h"
#include "Headers/graph.h"
#include "Headers/minHeap.h"
#include "Headers/dijkstra.h"

using namespace std;

int main(int num_args, char* arg[])
{
    //string variables containing 2nd and 3rd arguments
    string startCityCode = arg[1];
    string endCityCode = arg[2];

    //initialize -1 for possible error handling
    int startCityID = -1;
    int endCityID = -1;

    //Error handling, program must be ran with 3 arguments 
    if (num_args != 3)
    {
        cout << "Invalid input, must have 2 arguments" << endl;
        return 1;
    }

    //Welcome message
    cout << "Author: Nathan Lam and Alex Parviz" << endl;
    cout << "Date: 12/6/2024" << endl;
    cout << "Course: CS311 (Data structures and Algorithms)" << endl;
    cout << "Description : Program to find the shortest route between cities" << endl;
    cout << "----------------------------------------------------------------" << endl;


    //Create map from city.txt
    //cityID is key, City struct is value
    map<int, City> cityMap = CreateCityMap();

    //get size of cityMap and initialize graph
    int numCities = cityMap.size();
    graph cityGraph(numCities);

    //add edges to graph from roads.txt
    AddRoadsToGraph(cityGraph);

    //try catch for error handling, cityID doesnt match any key in cityMap
    try
    {
        //search map for key that matches the 2 given cityIDs
        startCityID = getCityID(startCityCode, cityMap);
        endCityID = getCityID(endCityCode, cityMap);
    }
    catch(string invalidCityCode)
    {
        cout << "Invalid city code: " << invalidCityCode << endl;
        return -1;
    }

    //arg[0] is a.out, arg[1] is the first argument, arg[2] is second argument
    cout << "From City: " << cityMap[startCityID].cityName << ", population " << cityMap[startCityID].pop << ", elevation " << cityMap[startCityID].elev << endl;
    cout << "To City: " << cityMap[endCityID].cityName << ", population " << cityMap[endCityID].pop << ", elevation " << cityMap[endCityID].elev << endl;

    //calculate shortest route from start to end using DijkstraShortestPath()
    //DijkstraShortestPath() calls ShowShortestDistance() which prints out the total distance and route
    //try-catch for error handling to catch "no possible route" exception
    try 
    {
        DijkstraShortestPath(cityGraph, startCityID, endCityID, cityMap);
    }
    catch (string errorMsg)
    {
        cout << "No route from " << errorMsg << endl;
        return 1;
    }

    //changed only Dijkstra.h arguments to pass endCityID and cityMap through DijkstraShortestPath, then passed again to showShortestPath()
    //did this so I can handle the printing in  showShortestPath since it uses the locator[] array. 
    //showShortestPath() only changed the cout << lines to match the project documentation
    //literally only had to add one line, fix the easy errors and it worked

    return 0;
}