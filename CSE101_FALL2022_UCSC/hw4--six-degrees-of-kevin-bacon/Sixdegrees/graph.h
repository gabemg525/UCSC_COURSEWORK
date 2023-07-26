// Filename: Graph.h
// 
// Header file for the class List that represents a linked list
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include "node.h"



class graph
{
	public:

		  unordered_map<string, node*> graphMap; 
      graph();
      void insert(char* actor, queue<char*> new_adjacents, char* movie);
      void insertMovie(string);
      string BFS(string,string);
      string BFSsolution(string,string);
      void cleanBFS();
		

};

#endif
