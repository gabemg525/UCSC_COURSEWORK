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

int main(int argc, char**argv)
{
    if(argc < 3)
    {
      throw std::invalid_argument("Usage ./hello <INPUT FILE> <OUTPUT FILE>");
    }
    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    
    LinkedList array_Lists[40];
    int i = 0;

    std::ifstream myfile("simple.txt");
    if(myfile.is_open()){
      string line;
      while(getline(myfile, line)){
        array_Lists[line.length()].insert(line);

      }
      myfile.close();
    }
    cout<<"lists made"<<endl;
    for(i = 5; i<40; i++){
      cout<<"ordering list:"<<endl;
      cout<<array_Lists[i].print()<<endl;
      
      array_Lists[i].order();
      cout<<"one list ordered:"<<endl;
      cout<<array_Lists[i].print() + "\n"<<endl;
      

    }
    
    
    string command, AR;
    char *length, *rank, *com;
    int l, r;

    while(getline(input, command)){
      
      if (command.length() == 0) // command is empty
            continue;
      com = strdup(command.c_str());
      length = strtok(com, " \t"); 
      rank = strtok(NULL, " \t");
      l = atoi(length);
      r = atoi(rank);
        output<<"words of length "<<length<<":"<<endl;
        output<<"    "<<array_Lists[l].print()<<endl;
      output<<array_Lists[l].atrank(r)<<endl;


    }

    input.close();
    output.close();

}