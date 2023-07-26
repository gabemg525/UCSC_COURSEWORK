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

void LinkedList :: insert(string word)
{
  Node *to_inc = find(word);
  if(to_inc==NULL){
    Node *to_add = new Node;
    to_add->data = word;
    to_add->next = head;
    to_add->freq = 1;
    to_add->rank = -1;
    head = to_add;
  }else{
    to_inc->freq++;

  }
  
}

Node* LinkedList :: find(string word)
{
  Node *curr = head;
  while(curr!=NULL)          
  {


    if(curr->data==word)
    {
      return curr;
    }
    curr = curr->next;
  }

  return NULL;
}

string LinkedList :: atrank(int R)
{
  Node *curr = head;
  while(curr!=NULL)
  {
    if(curr->rank==R)
    {
      return curr->data;
    }
    curr = curr->next;
  }
  return "";
}

string LinkedList :: print()
{
  string list_str = "";
  Node *curr = head;
  while(curr!=NULL){
    list_str = list_str + curr->data + " " + to_string(curr->freq) + " ";
    curr = curr->next;
  }
  if (list_str.length()>0)
    list_str.pop_back();
  return list_str;
}

void LinkedList :: swap(Node* n1, Node* n2)
{
  if(n1==NULL || n2==NULL){
    cout<<"couldn't find node(s) to swap"<<endl;
    return;
  }


  Node* prevn1 = head;
  Node* prevn2 = head;
  Node* temp = head;


  while(prevn1->next!=NULL){
    if(prevn1->next->data==n1->data){
      break;
    }
    prevn1=prevn1->next;
  }
  while(prevn2->next!=NULL){
    if(prevn2->next->data==n2->data){
      break;
    }
    prevn2=prevn2->next;
  }

  if(n1->data==head->data){
    prevn2->next=n1;
    temp = n2->next;
    n2->next = n1->next;
    n1->next = temp;
    head = n2;
    return;
  }
  if(n2->data==head->data){
    prevn1->next=n2;
    temp = n1->next;
    n1->next = n2->next;
    n2->next = temp;
    head = n1;
    return;
  }  
  prevn1->next=n2;
  prevn2->next=n1;
  temp = n1->next;
  n1->next = n2->next;
  n2->next = temp;

  return;
}

void LinkedList :: order()
{
  if(head==NULL){
    cout<<"no list"<<endl;
    return;
  }
  bool sorted = false;
   int i = 0;
  Node* prefix;
  Node* suffix;
  Node* temp = NULL;
  while(sorted!=true){
    sorted = true;
    prefix=head;
    suffix=head->next;
    while(suffix!=NULL){
      
      if(prefix->freq<suffix->freq){
        //cout<<"swap 1"<<endl;
        temp = suffix;
        swap(prefix,suffix);
        suffix = prefix;
        prefix = temp;
        sorted = false;
      }
      if(prefix->freq==suffix->freq && prefix->data>suffix->data){
        //cout<<"swap 2"<<endl;
        // cout<<"Before swap prefix: " + prefix->data + " suffix: " + suffix->data<<endl;
        temp = suffix;
        swap(prefix,suffix);
        suffix = prefix;
        prefix = temp;
        sorted = false;
        // cout<<"After swap prefix: " + prefix->data + " suffix: " + suffix->data<<endl;
      }
      
      
      prefix=prefix->next;
      suffix=suffix->next;

      
    }
    
    i++;
  }
  cout<< to_string(i) + " "<<endl;
  
  int r = 0;
  temp = head;
  temp->rank=r;
  while(temp->next!=NULL){
    temp=temp->next;
    r++;
    temp->rank=r;
  }
  return;
}