
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#include "minHeap.h" //include your min heap class. It will be used in Dijkstra's algorithm
#include "graph.h" // include  your graph class. You will pass a graph to Dijkstra's algorithm

//Each vertex has a vertex number, current shortest distance and predecessor
struct vertex
{
  int vertexNum; //the vertex number
  int curDist; //the current shortest distance from start to the vertex 
  int predecessor; //the predecessor along the shortest path to the vertex
};

int* locator; ///tells where each vertex exists within the heap. The dynamic array pointed to by this pointer will be created inside dijkstraSHortestPath() down below
//e.g. vertex numbers in heap[3, 1, 2, 4, 0] vertex 3 is at the root because its curDist is the smallest
//     locator should look like this [4, 1, 2, 0, 3] vertex 3 can be found at 0. vertex 0 can be found at 4 in heap
//This is a global variable (sounds terrible), but that is ok for this application. The reason why it is declared global is that it is accessed from mySwap() down below. mySwap() is called from the min heap class. We are not passing locator to the min heap class.


//this will be called from the min heap class. Each element in the heap is a vertex which consists of vertexNum, curDist and predecessor.
//The heap is maintained by curDist. 
bool operator<(const vertex& v1, const vertex& v2)
{
  //compare the curDistances of v1 and v2
  return v1.curDist < v2.curDist;
}

//this will be called from the min heap class
bool operator>(const vertex& v1, const vertex& v2)
{
  //compare the curDistances of v1 and v2
  return v1.curDist > v2.curDist;
}

/**********************************************************************************
Swaps two vertices.

Paramenter1: vertex& v1, a vertex object
Parameter 2: vertex& v2, a vertex object
**********************************************************************************/
void mySwap(vertex& v1, vertex& v2)
{
  //swap 2 vertices
  vertex temp = v1;
  v1 = v2;
  v2 = temp;
  //Throughout this template, one line of ?s doesn't mean you can only have 1 statement. You can have multiple statmenets.
  
  //the locations of the 2 vertices need to be swapped as well.  locator is a global pointer declared above
  int tempLocator = locator[v1.vertexNum];
  locator[v1.vertexNum] = locator[v2.vertexNum];
  locator[v2.vertexNum] = tempLocator;
}

//This will be called from printHeapArrays() down below. printHeapArrays() should be used for debugging your code. 
ostream& operator<<(ostream& o, const vertex& v)
{
  //output the 3 values of the vertex, v.  You could Output them in this format [vertexNum, curDist, predecessor]
  o << "[" << v.vertexNum << ", " << v.curDist << ", " << v.predecessor << "]";
  return o;
}

//print the min heap and locator array for debugging
//num_ver is the total number of vertces.
void printHeapArrays(const minHeap<vertex>& h, const int* locator, int num_ver)
{
  //This functions is complete. 
  cout << "----- heap ------" << endl;
  cout << h << endl; //operator<<() in min heap class is called here, which calls operator<<(ostream, vertex) above

  cout << "----- locator ------" << endl;
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << locator[i] << " ";                                                                                               
  cout << endl;
}


/**********************************************************************************
This function shows the path from start vertex to destination vertex and prints the route city by city

Paramenter1: const minHeap<vertex>& MH, a minHeap object containing the vertices in minHeap status
Parameter 2: int start, the starting vertex
Parameter 3: int dest, the destination vertex
Parameter 4: map<int, City>& cityMap, the map data structure containing the city information
**********************************************************************************/
void showShortestDistance(const minHeap<vertex>& MH, int start, int dest, map<int, City>& cityMap)
{
    //trace the shortest path from dest back to start
    stack<int> path;
    int top;
    int totalDistance;
    string startCityName = cityMap[start].cityName;
    string destCityName = cityMap[dest].cityName;

    for(int v = dest; v != -1; v = MH.getElem(locator[v]).predecessor)
    {
        path.push(v);
    }

    //store shortest possible distance from start to end
    totalDistance = MH.getElem(locator[dest]).curDist;

    //if this is 9999, we know from curDist being initalized as 9999 that there is no possible route from start to dest
    //throw start and end so we can print in error handling try-catch
    if (totalDistance == 9999)
    {
        string errorMsg = startCityName + " to " + destCityName;
        throw (errorMsg);
    }

    //prints shortest possible distance 
    cout << "The shortest distance from " << startCityName << " to " << destCityName << " is " << MH.getElem(locator[dest]).curDist << endl;

    cout << "through the route: ";
    while (!path.empty()) 
    {
        top = path.top(); //Access the top element
        cout << cityMap[top].cityName; //print top element
        path.pop(); //Remove the top element
        
        //checks if its last in the route to add arrow or not
        if (!path.empty())
        {
            cout << "->";
        }
    }
    cout << endl;
}

/**********************************************************************************
This function performs dijkstra's algorithm on a given graph starting from a given position and ending and a specified point

Paramenter1: const graph& g, a graph object containing the road information
Parameter 2: int start, the starting vertex
Parameter 3: int end, the end vertex
Parameter 4: map<int, City>& cityMap, the map data structure containing the city information
**********************************************************************************/
void DijkstraShortestPath(const graph& g, int start, int end, map<int, City>& cityMap)
{
  
  minHeap<vertex> toBeChecked(g.getNumVer()); //Create a min heap of the data type, vertex.
  

  //The following for loop populates the min heap with all the vertices. Set curDist to 999 and predecessor to -1.
  //e.g. vertex for vertext number 0 should like this [0, 999, -1]
  //     vertex for vertext number 1 should like this [1, 999, -1]
  vertex ver; //temp vertext struct used for multiple purposes 
  for (int i = 0; i < g.getNumVer(); i++)
    {
      //fill ver (declared above) with 3 values
      ver.vertexNum = i;
      ver.curDist = 9999;
      ver.predecessor = -1;
      //call minHeap::insert() to insert each vertex
      toBeChecked.insert(ver);
    }
 

  
  
  locator = new int[g.getNumVer()]; //Create a dynamic array pointed to by locator, which is declared globally above.
  //locator is an array containing the location of each vertex in the heap
  //locator[0] always tells the location/index of vertex 0 in the heap. If the locator looks like [3, 0, 1, 2], vertex 0 is located at index 3 in the heap, veertex 1 is located at index 0 (meaning vertex 1 has the minimum distance).
  
  
  
  for(int i = 0; i < g.getNumVer(); i++){
    locator[i] = i;}//You need to initialize the locator array. To start with, locator array should look like this [0, 1, 2, 3, 4, ...] telling us vertex 0 is at index 0 in the heap, vertex 1 is at index 1
  
 
  
  //fill ver (declared above) with start, 0 and -1. start vertex should have 0 for curDist and -1 for predecessor
  //If start is 3, ver should look like [3, 0, -1] 
  ver.vertexNum = start;
  ver.curDist = 0;
  ver.predecessor = -1;
  //call minHeap::updateElem() to update the start vertex's info
  //cout << "__________________________" << endl;
  toBeChecked.updateElem(locator[start], ver);
  //the updateElem() will update the info at index i (first parameter). 
  //updateElem() will fix the min heap based on curDist starting at i.
  //Since this start vertex has 0 for curDist and the other vertices have 999 for curDist,
  //this start vertex should come up to the top
  

  //******** Follow Dijkstra's algorithm in the lecture notes and complete the following ***********
  
  //Use printHeapArrays() for debugging
  
  //After Dijkstra's algorithm is finished, call showShortestDistance() above to show the path and distance from start and destination

  //printHeapArrays(toBeChecked, locator, toBeChecked.getNum());
  //cout << "___" << endl;
  //Don't forget to destroy the dynamic array you made for locator
   while(toBeChecked.getNum() != 0){

     vertex v = toBeChecked.getMin(); // v = vertex in heap with min dist
     toBeChecked.remove(0); //remove v from min heap
     
     for(const edge* e : g.getVerAr()[v.vertexNum]){
       int u = e->getNeighbor(); //get vertex of u
       int weight = e->getWt(); //get weight of u

       //check if u is in heap, only do the following if so
       if(locator[u] < toBeChecked.getNum()){ //if locator of u = -1 then it's not in heap
	
	 if(toBeChecked.getElem(locator[u]).curDist > v.curDist + weight){
	   
	   toBeChecked.getElem(locator[u]).curDist = v.curDist + weight; //update curDist 
	   toBeChecked.getElem(locator[u]).predecessor = v.vertexNum; //set predecessor
	   toBeChecked.updateElem(locator[u],  toBeChecked.getElem(locator[u])); //Update position in heap
	 }}}}

 
   showShortestDistance(toBeChecked, start, end, cityMap);

   delete[] locator;
}


