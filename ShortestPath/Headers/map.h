#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <queue>
#include <list>
#include <string>
#include <sstream>
#include "graph.h"


using namespace std;

struct City
{
    int cityID;
    string cityCode;
    string cityName;
    int pop;
    int elev;
};

struct Road
{
    int start, end, distance;
};

/**********************************************************************************
Creates a map of city information by reading in from a text file.
Returns the newly created map.
**********************************************************************************/
map<int, City> CreateCityMap()
{
    map<int, City> cityMap; //map that has all cities from city.txt, key is cityNum and value is a City struct
    ifstream finCity("Resources/city.txt");   //file reader CHANGE TO "city.txt" FOR EMPRESS

    int cityID, pop, elev; //ints city ID, population, and elevation
    string cityName, cityCode; //strings city name and abbreviation

    //city.txt error handling
    if (!finCity) 
    {
        cerr << "Error: Unable to open city.txt\n";
        return cityMap;
    }


    //Opens city.txt and reads in cities. 
    //Adds them to a map that uses the city ID as the key and the value is a City struct
    while (finCity >> cityID >> cityCode >> cityName >> pop >> elev)
    {
        cityMap[cityID] = { cityID, cityCode, cityName, pop, elev };
    }

    finCity.close();

    return cityMap;
}

/**********************************************************************************
Fills a graph of road information by reading in from a text file.
Returns the newly created weighted graph.
Parameter1: graph& citiesGraph, the graph to be filled
**********************************************************************************/
void AddRoadsToGraph(graph& citiesGraph)
{
    ifstream finRoad("Resources/road.txt");    //file reader
    int start, end, distance; //temp variables

    //road.txt error handling
    if (!finRoad) 
    {
        cerr << "Error: Unable to open road.txt\n";
        return;
    }

    //Opens roads.txt and reads in roads
    //Adds them to a map that uses the city ID as the key and the value is a City struct
    while (finRoad >> start >> end >> distance)
    {
        citiesGraph.addEdge(start, end, distance);
    }

    finRoad.close();
}

//takes cityCode string input and searches cityMap for matching key
//return integer key
/**********************************************************************************
Takes in a cityCode string as input and searches cityMap for matching key.
Returns a city ID.
Parameter1: string cityCode, the city code used to search the map
Parameter2: map<int, City>& cityMap, the map to be searched
**********************************************************************************/
int getCityID(string cityCode, map<int, City>& cityMap)
{
    int cityID;

    for (const auto& city : cityMap)
    {
        if (city.second.cityCode == cityCode)
        {
            cityID = city.first;
            return cityID;
        }
    }

    //throw cityCode so that error message can display the invalid cityCode
    throw(cityCode);
}