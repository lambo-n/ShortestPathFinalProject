#include <iostream>
#include <cstdlib>
#include <map>
#include "map.h"
#include "graph.h"

using namespace std;

int main(int num_args, char* arg[])
{
    //string variables containing 2nd and 3rd arguments
    string startCityCode = arg[1];
    string endCityCode = arg[2];

    //will be parsed from string, initialized -1 for error handling
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
    graph citiesGraph(numCities);

    //add edges to graph from roads.txt
    AddRoadsToGraph(citiesGraph);

    //get startCityID
    for (const auto& city : cityMap)
    {
        if (city.second.cityCode == startCityCode)
        {
            startCityID = city.first;
            break;
        }
    }

    //get endCityID
    for (const auto& city : cityMap)
    {
        if (city.second.cityCode == endCityCode)
        {
            endCityID = city.first;
            break;
        }
    }

    //error handling, usually problem reading input file
    if (startCityID == -1 || endCityID == -1)
    {
        cerr << "Error parsing string arguments to integers" << endl;
        return 1;
    }

    //arg[0] is a.out, arg[1] is the first argument, arg[2] is second argument
    cout << "From City: " << cityMap[startCityID].cityName << ", population " << cityMap[startCityID].pop << ", elevation " << cityMap[startCityID].elev << endl;
    cout << "To City: " << cityMap[endCityID].cityName << ", population " << cityMap[endCityID].pop << ", elevation " << cityMap[endCityID].elev << endl;

    //print out shortest route from start to end
    //The shortest distance from ANAHEIM to BAKERSFIELD is 225
    //through the route : ANAHEIM->VICTORVILLE->CHINO->GRPVE->ISABELLA->BAKERSFIELD


    return 0;
}