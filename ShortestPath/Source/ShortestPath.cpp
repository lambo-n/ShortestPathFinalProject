#include <iostream>
#include <cstdlib>
#include "..\Headers\dijkstra.h"
#include "..\Headers\graph.h"
#include "..\Headers\minHeap.h"
#include "map.cpp"


using namespace std;

int main(int num_args, char* arg[])
{
    //there was 1 argument passed to main
    if (num_args != 3)
    {
        cout << "Invalid input, must have 2 arguments" << endl;
        return 1;
    }

    //Here is where we will probably map arg[1] and arg[2]



    //Welcome message
    cout << "Author: Nathan Lam and Alex Parviz" << endl;
    cout << "Date: 12/3/2024" << endl;
    cout << "Course: CS311 (Data structures and Algorithms" << endl;
    cout << "Description : Program to find the shortest route between cities" << endl;
    cout << "----------------------------------------------------------------" << endl;

    //arg[0] is a.out, arg[1] is the first argument, arg[2] is second argument
    cout << "From City: " << arg[1] << " Population: 0" << ", elevation 0" << endl;
    cout << "To City: " << arg[2] << " Population: 0" << ", elevation 0" << endl;

    return 0;
}