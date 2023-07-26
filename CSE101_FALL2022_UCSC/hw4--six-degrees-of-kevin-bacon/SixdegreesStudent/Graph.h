// Filename: Graph.h
// 
// Header file for the class List that represents a linked list
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#ifndef LIST_H
#define LIST_H
#include "Node.h"
class Graph
{
	public:
		queue<Node*> Nqueue; 
		Graph();
		void deleteList();
    void insert(char*, queue<char*>, char*); // Inserts word into list
    void insertMovie(string);
    Node* find(char*);  // find the node that contains string. If none exists, return NULL
    void printAdj(char*);

    string BFS(char*, char*);
    string BFSsolution(char*,Node*);
};

#endif
