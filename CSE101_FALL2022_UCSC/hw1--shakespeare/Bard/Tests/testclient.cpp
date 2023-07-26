#include <iostream>
#include "linkedlist.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;
    ofstream output;

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string word_to_add; 
  
    
    
    LinkedList myList; // initializing the linked list
    
    //testing LinkedList::insert
    int n;
    char *char_array;
    while(getline(input,word_to_add)){

      char_array = new char[word_to_add.length()+1];
      strcpy(char_array, word_to_add.c_str());
      myList.insert(char_array);
      
    }

    output << myList.print() << endl;


    
    
    input.close();
    output.close();
}
