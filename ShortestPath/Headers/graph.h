
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <string>

using namespace std;

class edge
{
  friend class graph;  //What do you need here if you want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w;};

  //for dijkstra's:
  int getNeighbor() const;
  int getWt() const;
};

//implementing dijkstra funcs here:
int edge::getNeighbor() const{
  return neighbor; //gets neighbor val
}
int edge:: getWt() const{
  return wt; //gets weight
}

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);

  //for dijkstra's:
  int getNumVer() const;
  list<edge*>* getVerAr() const;
};

//implementing dijkstra funcs:
int graph::getNumVer() const{
  return num_ver; //gets num of vertices
}
list<edge*>* graph::getVerAr() const{
  return ver_ar; //gets vertex array
}

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object

  num_ver = num; //set num of vertices
  ver_ar = new list<edge*>[num_ver]; //dynamic array with num_ver number of slots, each a list object

}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  

  for(int i = 0; i < num_ver; i++){
    for(edge* e : ver_ar[i]){
      delete e;}}

  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array

  delete[] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.


  ver_ar[v].emplace_back(new edge(u, w)); //create new edge object to add at end of list for ver_ar[v]

  
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  //I created a queue object of string data type from the library's queue class to save all the paths.

  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.

  int* num = new int[num_ver]; //ar to keep track of visited vertices
  for(int i = 0; i<num_ver; i++){
    num[i] = 0; //Init all as unvisited
  }

  queue<string> edges; //Store edges as strings
  int i = 1;

  for (int v = 0; v < num_ver; v++) {
    if (num[v] == 0) {        //If v unvisited
      DFT_helper(v, i, num, edges); //Start DFT from this vertex
    }
  }

  //You could call displayQueue() implemented above to display all the paths. 

  displayQueue(edges);
  
  //Don't forget to destroy the dynamic array

  delete[] num;
  
}

//I made the following function to see if there are still unvisited nodes. Start looking at s, which is the one after the vertext we started last time. start point may not be 0. If start was 5, check the num array from index 6 then 7... until a zero is found (you may find a zero at index 1). Next time check from index 2.                                                                                            
//num is the array of vertices                                                                                                          
//start is the start vertex                                                                      
//s is the vertext right after the vertex we started last time                                                                          
int graph::nextUnvisitedNodes(int* num, int start, int s)
{
  //go through the num array from s to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  //don't start from index 0!
  //Althought this function may be called multiple times because there may be multiple disconnected graphs, we are checking each vertex only once.

  
      //Loop through num array from index s to the end
    for (int i = s; i < num_ver; i++) {
        if(num[i] == 0) {  //If the vertex is unvisited
            return i;  //Return the index of the unvisited vertex
        }
    }
    
    //If no unvisited vertex found, return -1
    return -1;


}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  //The algorithm is in my lecture notes

  num[v] = i++;
  cout << v << " ";
  
  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
      int next = (*u)->neighbor;
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  

      if(num[next] == 0){

	//push each path e.g. 0->1 into q. to_string(int) converts int to string. 
	//to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp 
	q.push(to_string(v) + "->" + to_string((*u)->neighbor));
	DFT_helper(next, i, num, q);
      }
    }
}
  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp 
   **********************************************************************************************
   ***********************************************************************************************/


//start is the index for the start vertex
void graph::BFT(int start)
{
  //The algorithm is in my lecture notes

  int* num = new int[num_ver]; //ar to keep track of visited vertices
  for(int i = 0; i<num_ver; i++){
    num[i] = 0; //Init all as unvisited
  }
  
  //Use the queue class from the library
  queue<int> q;
  //I used another queue of strings to save all the paths.
  queue<string> edges;

  int i = 1;

  do{
    //if first vertex unvisited, add to queue and update visited status
    if(num[start] == 0){
      num[start] = i++;
      q.push(start);}

    //If queue not empty, get front
    while(!q.empty()){

      int v = q.front();
      q.pop();

      cout << v << " ";

      for(edge* e : ver_ar[v]){
	int u = e->neighbor; //get neighbor of cur vertex

	if(num[u] == 0){
	  num[u] = i++;
	  q.push(u);
	  edges.push(to_string(v) + "->" + to_string(u));}}}
    start = nextUnvisitedNodes(num, start, start+1);
  }while(start != -1);
 
  

  displayQueue(edges);

   delete[] num;
   
}

#endif
