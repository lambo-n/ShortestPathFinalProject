/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Alex Parviz
Your programmer number: 23
Hours spent making and testing your min heap class: 2
Any difficulties?:  Some small difficulties remembering how to override the "<<" operator 
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;
//#include "swap.h" //for mySwap().  If you didn't create it, you can use the library's swap()

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete[] ar; ar = NULL;}
  void min_heapify(int i);
  //void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();

  //for dijkstra's:
  T& getElem(int i);
  const T& getElem(int i) const;
  int getCap() const;
  int getNum() const;
  void updateElem(int i, const T& newValue);

  class Underflow{};
  class Overflow{};
  class BadIndex{};
  class NotFound{};
};

//implement funcs for dijkstra's:
template <class T>
T& minHeap<T>::getElem(int i) {
  if (i < 0 || i >= getCap()) {
      throw BadIndex(); //make sure i is valid
    }
    return ar[i]; //return the elem at ar[i]
}


template <class T>
const T& minHeap<T>::getElem(int i) const {
  if (i < 0 || i >= getCap()) {
        throw BadIndex(); //make sure i is valid
    }
    return ar[i]; //return the elem at ar[i]
}

template <class T>
int minHeap<T>::getCap() const {
  return capacity; //return capacity, the size of ar
}

template <class T>
int minHeap<T>::getNum() const {
  return num; //return num of elems in ar
}

template <class T>
void minHeap<T>::updateElem(int i, const T& newValue) {
    if (i < 0 || i >= num) {
        throw BadIndex();
    }
    ar[i].curDist = newValue.curDist;
    ar[i].predecessor = newValue.predecessor;

    //Re-heapify to maintain the heap property
    bubbleUp(i);
    min_heapify(i);
}

//You need to implement all the memeber functions above.  Don't forget operator<<().


template <class T>
minHeap<T>::minHeap(int c) {

  if(c <= 0){ throw Overflow();}
 
  capacity = c;
  num = 0;
  ar = new T[capacity]; // Allocate memory for the dynamic array
}

//implement min_heapify
template <class T>
void minHeap<T>::min_heapify(int i) {

  //the parent index and its children
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < num && ar[left] < ar[smallest])
        smallest = left;

    if (right < num && ar[right] < ar[smallest])
        smallest = right;

    if (smallest != i) {
        mySwap(ar[i], ar[smallest]);

	//locator[ar[i].vertexNum] = i;
        //locator[ar[smallest].vertexNum] = smallest;
	
        min_heapify(smallest);
    }
}

template <class T>
void minHeap<T>::bubbleUp(int i) {
  //get the smallest value to its proper place, make sure i is valid
  //cout << "TESTING" << endl;  //used to debug
  while (i != 0 && ar[(i - 1) / 2] > ar[i]) {

    //cout << "TEST BUBBLE" << endl;  //used to debug
    mySwap(ar[i], ar[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h) {
    for (int i = 0; i < h.num; i++) {
        o << h.ar[i] << " ";
    }
    return o;
}


template <class T>
void minHeap<T>::insert(const T& el) 
{
  if(num >= capacity)
    throw Overflow(); //"The array is full";

  ar[num] = el;
  num++;
  bubbleUp(num - 1);
}

template <class T>
int minHeap<T>::find(const T& key) const
{
  T temp = key;
  for(int i = 0; i < num; i++) 
    if(ar[i].vertexNum == temp.vertexNum)
      return i;

  //The element doesn't exist 
  return -1;// "The element doesn't exist";                                                                                             
}

template <class T>
void minHeap<T>::remove(int i) {
  if (i < 0 || i >= num){
    throw BadIndex();} //"The element doesn't exist"; 

    mySwap(ar[i], ar[num - 1]);
    num--;
    min_heapify(i);
}


template <class T>
T minHeap<T>::getMin() {
  //if heap empty, throw Underflow
    if (num == 0)
        throw Underflow(); // "The heap is empty";
    
    //sets minValue to top and returns it
    T minValue = ar[0];
    //remove(0);
    return minValue;
}

#endif
