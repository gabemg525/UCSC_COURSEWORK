#include <iostream>
#include "LinkedList.h"
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

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *val, *val2, *op; // for using with strtok, strtol


    LinkedList myList; // initializing the linked list
        
    
    while(getline(input,command)) // get next line of input, store as repeat
    {
        if (command.length() == 0) // command is empty
            continue;
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " \t"); //tokenize command on whitespace, first token is operation

        // We first check if command is to print, since we do not need further parsing of command
        if(strcmp(op,"p") == 0) // print list
        {
            output << myList.print() << endl; // write printed list to file, and add new line
            cout << "Printing" << endl;
            cout << myList.print() << endl; // printing to console
            continue; // move on to next command
        }

        val = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        val2 = strtok(NULL, " \t");
        
        if(strcmp(op,"i") == 0) // insert into list
        {
            cout << "Insert "+std::string(val) << endl;
            myList.insert(val);
        }

        if(strcmp(op,"f") == 0) // insert into list
        {
            cout << "Find "+std::string(val) << endl;
            if(myList.find(val)==NULL){
              cout << " Not found" << endl;
            
            } else {
              cout << "Found " << endl;
            
            }
        }
        // if(strcmp(op,"s") == 0) // insert into list
        // {
        //     cout << "Swap "+std::string(val) + " and " +std::string(val2) << endl;
        //     myList.swap(val, val2);
          
        // }

        if(strcmp(op,"o") == 0) // insert into list
        {
            cout << "Order List" << endl;
            myList.order();
          
        }



    
     }

    //  cout << myList.head->next->data << endl;

     input.close();
     output.close();
}