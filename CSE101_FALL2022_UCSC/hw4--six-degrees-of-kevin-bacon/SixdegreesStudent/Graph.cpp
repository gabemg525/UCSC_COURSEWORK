#include <iostream>
#include "Node.h"
#include "Graph.h"
#include <stack>
#include <string.h>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

Graph :: Graph()
{
  queue<Node*> initial_Nqueue;
	Nqueue = initial_Nqueue;
}

// Inserts word into list, with frequency 1. 
// Input: String to insert into the linked list
// Output: Void, just inserts new node at head of the list.
void Graph :: insert(char* actor, queue<char*> new_adjacents, char* movie)
{
  Node* to_insert = find(actor);
  
  if(to_insert==NULL){
    Node *new_insert = new Node(actor);
    to_insert = new_insert;
    Nqueue.push(to_insert);
  }
  queue<char*> tempQ = new_adjacents;
  Pair adj_to_add;
  adj_to_add.adjM = movie;
  while(!tempQ.empty()){
      adj_to_add.adjA = tempQ.front();
      to_insert->adjacents.push(adj_to_add);
      tempQ.pop();
  }
  
	return; 
}

void Graph :: insertMovie(string input_str){
    char *movie, *actor, *in_str;
    queue<char*> movie_actors;

    in_str = strdup(input_str.c_str());       
    movie = strtok(in_str, " \t");
    cout<<movie<<endl;
    actor = strtok(NULL, " ");

    while(actor!=NULL){                       
        movie_actors.push(actor);
        actor = strtok(NULL, " ");
    }
    int s = movie_actors.size();
    char* front;
    for(int i=0; i<s; i++){
        front = movie_actors.front();
        movie_actors.pop();
        insert(front, movie_actors, movie);
        movie_actors.push(front);
    }

}

Node* Graph :: find(char* actor){
    queue<Node*> tempQ = Nqueue;
    Node* curr;
    while(!tempQ.empty()){
        curr = tempQ.front();
        if(strcmp(curr->actor,actor)==0){
            return curr;
        }
        tempQ.pop();
    }
    return NULL;
}

void Graph :: printAdj(char* actor){
    Node* curr=find(actor);
    if(curr==NULL){
      return;
    }
    cout<<actor<<" adjacents: ";
    queue<class Pair> tempQ = curr->adjacents;
    Pair top;
    while(!tempQ.empty()){
        top = tempQ.front();
        cout<<top.adjA<<" "<<top.adjM<<" ";
        tempQ.pop();
    }
    cout<<endl;
    return;
    
}

string Graph :: BFS(char* source_actor, char* find_actor)
{
    Node* currN=find(source_actor);
    Node* findN=find(find_actor);
    if(currN==NULL||findN==NULL){
      return "Not present";
    }
    if(strcmp(source_actor,find_actor)==0){
      string to_return = source_actor;
      return to_return;
    }

    stack<Node*> recurStack, nextStack;
    recurStack.push(currN);
    Node* temp, *temp_adj;
    Pair tempPair;
    char* adj_top;
    queue<class Pair> temp_adjacents;
    while(!recurStack.empty()){
        while(!recurStack.empty()){
            
            temp = recurStack.top();
            cout<<"test1 finding adjacents of: "<<temp->actor<<endl;
            temp_adjacents = temp->adjacents;
            while(!temp_adjacents.empty()){
                tempPair = temp_adjacents.front();

                temp_adj = find(tempPair.adjA);
                cout<<"    test2 adjacent: "<<temp_adj->actor<<endl;
                
                if(temp_adj->visited==false){
                    temp_adj->visited=true;
                    temp_adj->parent=temp;
                    temp_adj->parent_movie=tempPair.adjM;
                    nextStack.push(temp_adj);
                }
                if(strcmp(temp_adj->actor, find_actor)==0){
                    return BFSsolution(source_actor, temp_adj);
                }
                
                temp_adjacents.pop();
            }
            
            recurStack.pop();
        }
        while(!nextStack.empty()){
            recurStack.push(nextStack.top());
            nextStack.pop();
        }
    }
    return "Not present";
}

string Graph :: BFSsolution(char* source_actor, Node* found){
    Node* temp = found;
    cout<<temp->actor;
    while(strcmp(temp->actor,source_actor)!=0){
        
        
        cout<<" "<<temp->parent_movie<<" "<<temp->parent->actor;
        temp=temp->parent;
        
    }
    cout<<endl;
    return "found that shit";
}

