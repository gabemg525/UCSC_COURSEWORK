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
    ifstream infile;
	  

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    int i, length, rank;
	  string word_to_add, word, svals; 
    
    char *char_array;
    LinkedList *myList;
    myList = new LinkedList[40];
    for(i=5; i<40; i++){
 //     cout << "h1" << endl;
      infile.open ("shakespeare-cleaned5.txt");
      while(getline(infile,word_to_add)) // To get you all the lines.
      {
        if(word_to_add.length() == i){
          char_array = new char[word_to_add.length()+1];
          strcpy(char_array, word_to_add.c_str());
          myList[i].insert(char_array);
          
        }

      
      }
//       output << myList[i].print() << endl;
      infile.close();
      
    }  



       while(input >> length >> rank){
         word = myList[length].get(rank);
         output << word << endl;

       }       

//     output << "-" << endl;
    infile.close();
    input.close();
    output.close();
    return 0;
}
