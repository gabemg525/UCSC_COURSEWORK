// Filename: Node.cpp
// 
// Contains the class Node that represents a node in linked list
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "Node.h"
#include <cstdlib>
#include <string>
#include <queue>
using namespace std;

// Default constructor
Node :: Node()
{
  actor = "";
  visited = false;
  parent = NULL;
  parent_movie = "";
	queue<class Pair> A;
  adjacents = A;


}

// Constructor with string input sets word and freq to 1
Node :: Node(char* a)
{
	actor = a;
  visited = false;
  parent = NULL;
  parent_movie = "";
  queue<class Pair> adj;
  adjacents = adj;

}


