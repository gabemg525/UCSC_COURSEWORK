// Filename: listwrapper.cpp
//
// This is the main wrapper for the LinkedList class.
// 
// After running make, the usage is:
//     ./listwrapper <INPUT_FILE> <OUTPUT_FILE>
// 
// The input file contains a list of operations performed on a linked list. The operations are insert, delete, and print. 
// Each line is of the form "i <INT>", "d <INT>", or "p". This means "insert", "delete", and "print" respectively. The second INT argument is for inserting/deleting that number.
// 
// Only the print operations generate output, which is the list printed in order in a single line.
// The output file contains the output of all print commands.
// 
// In addition, the console output shows the operations performed, and also prints the list (for every print command).
// Look at the associated pdf in this directory for more details.
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

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

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *dummy, *valstr, *val2str, *op; // for using with strtok, strtol
    int val, val2; // the value from the command

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

        valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if(valstr != NULL) // first check if there is actually anything to convert into int
            val = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details. 
    
        val2str = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if(val2str != NULL) // first check if there is actually anything to convert into int
            val2 = strtol(val2str, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details. 
    
        if(strcmp(op,"i") == 0) // insert into list
        {
            cout << "Insert "+to_string(val) << endl;
            myList.insert(val);
        }
        if(strcmp(op,"d") == 0) // delete from list
        {
            cout << "Delete "+to_string(val) << endl;
            myList.deleteNode(val);
        }

        
        if(strcmp(op,"dr") == 0) // recursive delete list
        {
            cout << "Recursive delete "+to_string(val) << endl;
            myList.deleterec(val);
        }

        if(strcmp(op,"dk") == 0) // recursive delete list
        {
            cout << "Delete "+ to_string(val2) + "th " +to_string(val) << endl;
            myList.deletekth(val, val2);
        }

        if(strcmp(op,"dl") == 0) // delete last
        {
            cout << "Delete last "+to_string(val) << endl;
            myList.deletelast(val);
        }

        if(strcmp(op,"abf") == 0) // delete all but first
        {
            cout << "Delete all but first "+to_string(val) << endl;
            myList.allbutfirst(val);
        }
        
        if(strcmp(op,"rev") == 0) // reverse list
        {
            cout << "Reverse "+to_string(val) << endl;
            myList.reverse(val);
        }

        if(strcmp(op,"isp") == 0) // is palindrome list
        {
            cout << "Check if palindrome " << endl;
            if(myList.ispalindrome()){
                cout << "True, it is a palindrome" << endl;
            }else{
                cout << "False, it is not a palindrome" << endl;
            }

        }
        if(strcmp(op,"dup") == 0) // rotate list
        {
            cout << "Delete duplicates " << endl;
            myList.dedup();
            cout << "why papi 3" << endl;
        }
     }

    //  cout << myList.head->next->data << endl;

     input.close();
     output.close();
}
