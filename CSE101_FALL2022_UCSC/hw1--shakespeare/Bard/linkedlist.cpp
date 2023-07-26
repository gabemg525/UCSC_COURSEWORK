// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Gabriel Gorospe

#include "linkedlist.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
LinkedList :: LinkedList()
{
	head = NULL;
}

// Insert(char word): Inserts the int word into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: word to insert into the linked list
// Output: Void, just inserts new Node
void LinkedList :: insert(char *word)
{
    Node *N = this->find(word);
//   cout << "________________________" << endl;
    if (N != NULL) {
//       cout << "word exists" << endl;
//       if(N->next != NULL){cout << "next : " << N->next->data << N->next->freq << endl;}
//       if(N->prev != NULL){cout << "prev : " << N->prev->data << N->prev->freq << endl;}
      
      N->freq++;
//       cout << "freq of " << N->data << " : " << N->freq << endl;
    } else {
//       cout << "Inserting " << word << endl;
      N = new Node; // creates new Node
      N->data = new char[strlen(word)+1]; // sets the data to hold input word
      N->data = word;
      N->freq = 1;
      N->next = NULL;
      N->prev = NULL;

    }
  
      // sorting algorithm
      Node *curr = head;
      
      
      if ( curr == NULL ) { //if list is empty sets N to head
        
        this->head = N;
//         cout << "Insert in empty list" << endl;
        return;
      }
      while (curr != NULL) {
//         cout << "the head : " << head->data << endl;
        if (strcmp(head->data, N->data) == 0){
//           cout << "Incremented val is already head" << endl;
          return;
        }
        if (N->freq > curr->freq){
          if(strcmp(head->data, curr->data) == 0){
//             cout << "Set new head" << endl;
            this->head = N;
          }
          if(N->next != NULL){
            N->next->prev = N->prev;
          }
          if(N->prev != NULL){
            N->prev->next = N->next;
          }
          N->next = curr;
          
          if(curr->prev != NULL){
            curr->prev->next = N;
            N->prev = curr->prev;
          } else {
            
            N->prev = NULL;
          }
          curr->prev = N;
          
          return;
        } else if (N->freq == curr->freq) {
          if (strcmp(N->data, curr->data) < 0) {
            if(strcmp(head->data, curr->data) == 0){
//             cout << "Set new head" << endl;
            this->head = N;
            }
            if(N->next != NULL){
              N->next->prev = N->prev;
            }
            if(N->prev != NULL){
              N->prev->next = N->next;
            }
            N->next = curr;

            if(curr->prev != NULL){
              curr->prev->next = N;
              N->prev = curr->prev;
            } else {

              N->prev = NULL;
            }
            curr->prev = N;

            return;
          } else {
            if (curr->next == NULL){ //place at end
//               cout << "Insert at end equal freq" << endl;
              curr->next = N;
              N->prev = curr;
              N->next = NULL;
              
              return;
            } else if (strcmp(curr->next->data, N->data)==0) {
              return;
            } else {
              curr = curr->next;
            }
            
          }
        } else {
          if (curr->next == NULL){ //place at end
//             cout << "Insert at end" << endl;
            curr->next = N;
            N->prev = curr;
            N->next = NULL;
            
            return;
          } else if (strcmp(curr->next->data, N->data)==0) {
              return;
            } else {
              curr = curr->next;
          }
          
        }
        
      }
        
    
      return;
      
}

// find(int word): Finds a Node with data "word"
// Input: int to be found
// Output: a pointer to a Node containing word, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing word
Node* LinkedList :: find(char *word)
{

    
    Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    // curr will look over list. At every iteration, we will check if curr->data is word. If so, we are done. Otherwise, we proceed through the list.
    while ( curr != NULL ) //looping over list
    {
//       cout << "can find" << endl;
        if (strcmp(curr->data, word) == 0){ // found word, so return curr
            return curr;
        }
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, word not found
    return NULL;
}

string LinkedList :: get(int rank)
{
  Node *curr = head;
  if(curr == NULL){
      return "-";
  }
  string str;
  for(int i=0; i<rank; i++){
    if(curr->next == NULL){
      return "-";
    }
    curr = curr->next;
    
  }
  str = curr->data;
  return str;
}



// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print()
{
    string list_str = ""; // string that has list
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	// curr will loop over list. It prints the content of curr, and then moves curr to next Node.
	while(curr != NULL){ // looping over list
        list_str = list_str + curr->data + " "; //append string with current Node's data
		curr = curr->next; // proceed through list

	}
    if (list_str.length() > 0) // string is non-empty
        list_str.pop_back(); // remove the last (extra) space from string
    return list_str;
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length()
{
  int length = 0; // initialize length to zero
	Node *curr = head; // curr is ths current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	
	while(curr != NULL){ // looping over list
		length++; // increment length
		curr = curr->next; // proceed to next Node
	}
	return length;
}
