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
	  

    graph myGraph;

    string movie_to_add;

    // input.open(argv[1]); // open input file
    // output.open(argv[2]); // open output file
     infile.open ("cleaned_movielist.txt");
     while(getline(infile,movie_to_add)) // To get you all the lines.
     {
         myGraph.insertMovie(movie_to_add);
     }
     infile.close();

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    char* a1, *a2, *com;
    string actor1, actor2, to_out, command;
    while(getline(input,command)) 
    {
        if (command.length() == 0)
            continue;

        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        a1 = strtok(com, " \t");
        a2 = strtok(NULL, " "); 
        actor1 = a1;
        actor2 = a2;

        to_out = myGraph.BFS(actor1, actor2);
        output<<to_out<<endl;
        cout<<to_out<<endl;

    }


    // string to_output = myGraph.BFS("Brad_Pitt", "Amitabh_Bachchan");
    // cout<<to_output<<endl;

    // to_output = myGraph.BFS("Brad_Pitt", "Tom_Cruise");
    // cout<<to_output<<endl;

    // to_output = myGraph.BFS("Michael_Cera", "Viggo_Mortensen");
    // cout<<to_output<<endl;
    

     input.close();
     output.close();
    return 0;
}
