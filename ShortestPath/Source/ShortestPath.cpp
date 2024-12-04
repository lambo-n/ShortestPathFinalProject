#include <iostream>
#include <cstdlib>
#include "..\Headers\dijkstra.h"
#include "..\Headers\graph.h"
#include "..\Headers\minHeap.h"


using namespace std;

int main(int num_args, char* arg[])
{
    cout << "num_args = " << num_args << endl;
    if (num_args != 2)
    {
        cout << "Run as follows:   ./a.out number" << endl;
        return 1;
    }

    //there was 1 argument passed to main
    cout << "answer: " << 2 * atoi(arg[1]) << endl;   //arg[0] is a.out, arg[1] is the first argument, which is a c-string. atoi converts a c-string to int

    return 0;
}