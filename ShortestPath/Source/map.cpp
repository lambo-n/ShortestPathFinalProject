#include <iostream>
#include <cstdlib>
#include "..\Headers\dijkstra.h"
#include "..\Headers\graph.h"
#include "..\Headers\minHeap.h"
#include <fstream>
#include <map>
#include <queue>
#include <list>
#include <string>

using namespace std;

struct City {

    int cID, pop, elev; //ints city ID, population, and elevation
    string cName; //strings city code and city name;


};


int main() {

    map<string, City> cityInfo; //map called cityInfo that will use a string key (like 'AN' or 'BK') to grab info from an array

    ifstream fincity;
    int cID, pop, elev; //ints city ID, population, and elevation
    string cCode, cName; //strings city code and city name;

    //Opens city.txt and reads in the 20 cities. Adds them to a map called cityInfo that uses the city code as the key to access the other elements of the struct
    fincity.open("city.txt");
    if (!fincity)
        cout << "Error with opening city text file." << endl;
    else
    {
        fincity >> cID >> cCode >> cName >> pop >> elev;
        while (finroad)
        {
            cityInfo[cCode] = { cID, cName, pop, elev };
            fincity >> cID >> cCode >> cName >> pop >> elev;

        }

    }
    fincity.close();

    ifstream finroad;
    int c1, c2, rw; //city 1, city 2, road weight

	graph roads(19); //A graph of the roads from city to city along with their weights

    //Opens road.txt and reads in the 19 roads, adding edges and weights from the roads.
    finroad.open("road.txt");
    if (!finroad)
        cout << "Error with opening road text file." << endl;
    else
    {
        finroad >> c1 >> c2 >> rw; 
        while (finroad)
        {
            roads.addEdge(c1, c2, rw); //Adds edge from c1 to c2 with weight rw
            finroad >> c1 >> c2 >> rw;
        }

    }

    finroad.close;

}