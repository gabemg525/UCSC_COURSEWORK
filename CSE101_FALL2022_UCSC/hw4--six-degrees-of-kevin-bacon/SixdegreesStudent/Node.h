// Filename: Node.h
// 
// Header file for the class Node that represents a node in each linked list
// 
// Japheth Frolick, August 2019

#ifndef NODE_H
#define NODE_H
#include <string>
#include <queue>
#include <stdexcept>
using namespace std;

class Pair
{
  public:
    char* adjA;
    char* adjM;

};

class Node
{
	public:
    char* actor;
    bool visited;
    Node *parent;
    char* parent_movie;
		queue<class Pair> adjacents; // stores the word in the node
		Node(); //default constructor (never used)
		Node(char*); // Constructor creates Node with actor name

};

#endif