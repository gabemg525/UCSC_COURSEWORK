// Filename: node.h
// 
// Header file for the class Node that represents a node in each linked list
// 

#ifndef NODE_H
#define NODE_H
#include <string>
#include <queue>
#include <stdexcept>
#include <unordered_map>

using namespace std;

class node
{
    public:
        unordered_map<string, string> adjacents;
        node* parent;
        string pathactor;
        string pathmovie;
        bool visited;
        node();
};

#endif