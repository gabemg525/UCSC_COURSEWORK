// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "linkedlist.h"
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

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
void LinkedList :: insert(int val)
{
	Node *to_add = new Node; // creates new Node
	to_add->data = val; // sets the data to hold input val
	
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
}

// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node* LinkedList :: find(int val)
{
    Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    // curr will look over list. At every iteration, we will check if curr->data is val. If so, we are done. Otherwise, we proceed through the list.
    while(curr != NULL) //looping over list
    {
        if (curr->data == val) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, val not found
    return NULL;
}

Node* LinkedList :: gethead()
{
    return head;
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* LinkedList :: deleteNode(int val)
{
    Node* prev = NULL;
    Node* curr = head;
    while(curr != NULL) // loop over list, starting from head
    {
        if(curr->data == val) // we found Node with val, so break
            break; 
        //otherwise, proceed list
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    // at this point, curr points to Node with val. If curr is null, then val is not in the list.
    if (curr == NULL) // val not found
        return NULL; 
    // val is in list. Note that curr is not NULL. There is a case analysis now. If prev is null, then curr is head. So we delete head directly.
    // Otherwise, we delete the Node after prev.
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. Note that both curr and prev are not NULL
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    return curr;
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList :: deleteList()
{
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    Node *temp = NULL;

	// curr will loop over list. At every iteration, we first store a pointer to the next Node, and then delete the current Node.
    while(curr != NULL){ // Looping over list
		temp = curr->next; // store pointer to next Node in the list
		delete(curr); // delete the current Node
		curr = temp; // update curr to proceed through list
	}
	head = NULL;
    return;
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
        list_str = list_str + to_string(curr->data) + " "; //append string with current Node's data
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

Node* LinkedList :: deleterec(int val)
{
    if(head->data==val){
        Node* temp = head;
        head = head->next;
        temp->next = NULL;
        cout << "yes papi 1" << endl;
        return temp;
    }
    cout << "yes papi 2" << endl;
    return deleterec(val, head);
}

Node* LinkedList :: deleterec(int val, Node* prev)
{
    if(prev==NULL || prev->next==NULL){
        return NULL;
    }

    if(prev->next->data == val){
        Node* to_return = prev->next;
        prev->next = to_return->next;
        to_return->next = NULL;
        return to_return;
    }
    return deleterec(val, prev->next);
}

// deletes kth occurence of the value
Node* LinkedList :: deletekth(int val, int k)
{
    int kiter = k;
    if(head->data==val)
    {
        
        if(k==1){
            Node* temp = head;
            head = head->next;
            temp->next = NULL;
            cout << "yes papi 3" << endl;
            return temp;
        }
        kiter--;
    }
    cout << "yes papi 4" << endl;
    return deletekth(val, kiter, head);
}

Node* LinkedList :: deletekth(int val, int k, Node* prev)
{
    if(prev==NULL || prev->next==NULL){
        return NULL;
    }
    int kiter = k;
    if(prev->next->data == val){
        if(kiter==1){
            Node* to_return = prev->next;
            prev->next = to_return->next;
            to_return->next = NULL;
            return to_return;
        }
        kiter--;
    }
    return deletekth(val, kiter, prev->next);
}

Node* LinkedList :: deletelast(int val)
{
    Node* to_delete;
    if(find(val)==NULL){
        return NULL;
    }
    if(head->data==val){
        to_delete = head;
        if(head->next==NULL){
            head = head->next;
            to_delete->next = NULL;
            cout << "yes papi 5" << endl;
            return to_delete;
        }
        
        
    }
    cout << "yes papi 6" << endl;
    return deletelast(val, to_delete, head);
}

Node* LinkedList :: deletelast(int val, Node* Dprev, Node* prev)
{
    if(prev==NULL){
        return NULL;
    }
    Node* to_delete_prev = Dprev;
    if(prev->next->data == val){
        cout << "step 6.5" << endl;
        to_delete_prev = prev;
    }
    cout << "step 7" << endl;
    if(prev->next->next==NULL){
        cout << "step 8" << endl;
        Node* to_return = to_delete_prev->next;
        to_delete_prev->next = to_return->next;
        to_return->next = NULL;
        return to_return;
    }
        
    
    return deletelast(val, to_delete_prev, prev->next);
}

Node* LinkedList :: allbutfirst(int val)
{
    if(find(val)==NULL){
        return NULL;
    }
    
    int passed = 1;
    if(head->data==val){
        passed--;
    }
    return allbutfirst(val, passed, head);
}

Node* LinkedList :: allbutfirst(int val, int P, Node* prev)
{
    int passed = P;
    if(prev==NULL){
        return NULL;
    }
    while(prev->next->data==val){
        if(passed!=1){
            Node* temp = prev->next;      
            prev->next = temp->next;
            temp->next = NULL;
        }else{
            prev=prev->next;
            passed--;
        }
        if(prev->next==NULL){
            return find(val);
        }
    }

    if(prev->next->next==NULL){

        return find(val);
    }

    return allbutfirst(val, passed, prev->next);
}

void LinkedList :: reverse(int val)
{
    if(head==NULL || head->next==NULL){
        return;
    }
    Node *suffix = head->next;
    Node *prefix = head;
    Node *prevhead = head;
    head->next = NULL;
    int i = val;
    while(suffix!=NULL && i>1){
        Node* temp = suffix->next;
        suffix->next = prefix;
        prefix = suffix;
        suffix = temp;
        
        i--;
    }
    prevhead->next = suffix;
    head=prefix;

    



}


bool LinkedList :: ispalindrome(){
    if(head==NULL){
        return false;
    }
    if(head->next==NULL){
        return true;
    }
    int i=0;
    return ispalindrome(i);
}

bool LinkedList :: ispalindrome(int i)
{
    int countup = 0; 
    int countback = length()-i;
    cout << countback << endl;
    Node* left = head;
    Node* right = head;
    while(countup<i){
        left = left->next;
        countup++;
    }
    while(countback>1){
        right = right->next;
        countback--;
    }
    if(right->data!=left->data){
        return false;
    }
    if(countup==countback){
        return true;
    }
    return ispalindrome(i+1);

}

void LinkedList :: dedup() // delete duplicates
{
    
    if(head==NULL){
        return;
    }
    Node* prev;
    Node* first_occur;
    prev=head;
    first_occur=head;
    while(first_occur!=NULL && first_occur->next!=NULL){
        prev = first_occur;
        while(prev!=NULL && prev->next!=NULL){
            while(first_occur->data==prev->next->data){
                if(prev->next->next==NULL){
                    prev->next=NULL;
                    break;
                }
                prev->next=prev->next->next;      
            }
            prev=prev->next;   
        }
        first_occur=first_occur->next;
    }
    return;
}

