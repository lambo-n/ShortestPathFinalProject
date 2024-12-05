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



int main() {

    map<string, array<string, 4>> cityInfo; //map called cityInfo that will use a string key (like 'AN' or 'BK') to grab info from an array

    ifstream fincity;




    ifstream finroad;
    int c1, c2, rw; //city 1, city 2, road weight

	graph roads(19); //A graph of the roads from city to city along with their weights

    //Opens road.txt and reads in the 19 roads, adding edges and weights from the roads.
    finroad.open("road.txt");
    if (!finroad)
        cout << "Error with opening text file." << endl;
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