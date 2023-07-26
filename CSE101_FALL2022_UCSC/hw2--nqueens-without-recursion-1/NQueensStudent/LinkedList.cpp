#include "LinkedList.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

LinkedList :: LinkedList()
{
  head = NULL;
}

void LinkedList :: insert(int x, int y)
{
  Node* to_add = new Node;
  to_add->row = x;
  to_add->col = y;
  head=to_add;
}

Node* LinkedList :: find(int col, int row)
{

    
    Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    // curr will look over list. At every iteration, we will check if curr->data is word. If so, we are done. Otherwise, we proceed through the list.
    while ( curr != NULL ) //looping over list
    {
//       cout << "can find" << endl;
        if (curr->col==col&&curr->row==row){ // found word, so return curr
            return curr;
        }
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, word not found
    return NULL;
}

string LinkedList :: print()
{
    string list_str = ""; // string that has list
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	// curr will loop over list. It prints the content of curr, and then moves curr to next Node.
	while(curr != NULL){ // looping over list
        list_str = list_str + curr->col + " " + curr->row + " "; //append string with current Node's data
		curr = curr->next; // proceed through list

	}
    if (list_str.length() > 0) // string is non-empty
        list_str.pop_back(); // remove the last (extra) space from string
    return list_str;
}