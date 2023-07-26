#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

struct Node
{
  int row;
  int col;
  Node* next;
};


class LinkedList
{
  private:
    Node *head;
  public:
    LinkedList();
    void insert(int, int);
    Node* find(int, int);
    string print();
    void nqueens();
};

#endif