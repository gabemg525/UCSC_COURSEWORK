#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

struct Node
{
  string data;
  int freq;
  int rank;
  Node* next;
};

class LinkedList
{
  private:
    Node *head;
  public:
    LinkedList();
    void insert(string);
    Node* find(string);
    string atrank(int);
    string print();
    void swap(Node*, Node*);
    void order();
};

#endif