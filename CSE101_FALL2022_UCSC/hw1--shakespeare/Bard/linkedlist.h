// Filename: linkedlist.h
// 
// Header file for the class LinkedList that represents a linked list
// 
// Gabriel Gorospe

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

// node struct to hold data
struct Node
{
	Node *next;
  Node *prev;
  char* data;
  int freq;
};

class LinkedList
{
	private:
		Node *head; // Stores head of linked list
	public:
		LinkedList(); // Default constructor sets head to null
        void insert(char*); // insert string into list 
        Node* find(char*); // find int in list, and return pointer to node with that int. If there are multiple copies, this only finds one copy
 		string get(int);
    string print(); // Construct string with data of list in order 
		int length(); // Returns the length of the linked list
};

#endif