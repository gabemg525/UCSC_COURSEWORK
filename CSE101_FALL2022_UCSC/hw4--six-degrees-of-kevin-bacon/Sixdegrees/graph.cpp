#include <iostream>
#include "graph.h"
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

graph :: graph()
{
  unordered_map<string, node*> init_graphMap;
	graphMap = init_graphMap;
}

// Inserts word into list, with frequency 1. 
// Input: String to insert into the linked list
// Output: Void, just inserts new node at head of the list.
void graph :: insert(char* actor, queue<char*> new_adjacents, char* movie)
{
    string actor_str = actor;
    // cout<<actor<<endl;
    if(graphMap.find(actor_str)==graphMap.end()){
        graphMap[actor_str] = new node();
    }
    node* to_insert = graphMap.at(actor_str);
    queue<char*> new_adj_Q = new_adjacents;
    string movie_str = movie;
    while(!new_adj_Q.empty()){
        if(to_insert->adjacents[new_adj_Q.front()]==""){
            
            to_insert->adjacents[new_adj_Q.front()]=movie;
            // cout<<"insert that shit:    "<<new_adj_Q.front()<<" "<<to_insert->adjacents[new_adj_Q.front()]<<endl;
        }
        new_adj_Q.pop();
    }
}

void graph :: insertMovie(string input_str){
    char *movie, *actor, *in_str;
    queue<char*> movie_actors;

    in_str = strdup(input_str.c_str());       
    movie = strtok(in_str, " \t");
    // cout<<movie<<endl;
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


string graph :: BFS(string source_actor, string find_actor)
{
    if(graphMap.find(source_actor)==graphMap.end()||graphMap.find(find_actor)==graphMap.end())
    {
        return "Not present";
    }
    if(source_actor==find_actor){
      return source_actor;
    }
    stack<node*> recurStack, nextStack;
    recurStack.push(graphMap.at(source_actor));
    node *temp_adj;
    node *temp = graphMap.at(source_actor);
    temp->pathactor=source_actor;
    recurStack.push(temp);
    unordered_map<string, string> tempUM;
    while(!recurStack.empty())
    {
        while(!recurStack.empty())
        {
            temp = recurStack.top();
            
            tempUM = temp->adjacents;
 
            for (const auto & [ A, M ] : tempUM) {
                temp_adj = graphMap.at(A);
                if(temp_adj->visited==false){
         
                    temp_adj->visited=true;
                    temp_adj->parent=temp;
                    temp_adj->pathactor=A;
                    temp_adj->pathmovie=M;
                    if(A==find_actor){
                      string to_return = BFSsolution(source_actor, A);
                      cleanBFS();
                      return to_return;
                    }
                    nextStack.push(temp_adj);
                }
                
                
            }

            recurStack.pop();
        }
        while(!nextStack.empty()){
            recurStack.push(nextStack.top());
            nextStack.pop();
        }
    }
    cleanBFS();
    return "Not present";
    
}

string graph :: BFSsolution(string source, string found)
{

    cout<<"BFSsolution"<<endl;
    cout<<"source: "<<source<<" found: "<<found<<endl;

    node* temp = graphMap.at(found);
    for (const auto & [ A, M ] : temp->adjacents){
        cout<<A<<" "<<M<<" ";
    }

    string to_return = "";
    while(temp->pathactor!=source){

        to_return =  " -(" + temp->pathmovie + ")- "+temp->pathactor+to_return;
        temp=temp->parent;

    }
    to_return = source+to_return;
    cout<<to_return<<endl;

    
    return to_return;
}

void graph :: cleanBFS()
{
    for (const auto & [ A, N ] : graphMap) {
        N->parent=NULL;
        N->pathactor="";
        N->pathmovie="";
        N->visited=false;
    }
    return;
}