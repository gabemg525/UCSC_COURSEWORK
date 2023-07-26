#include "node.h"
#include <cstdlib>
#include <string>
#include <queue>
using namespace std;

node :: node()
{

    unordered_map<string, string> init_adjacents;   // key is the adjacent actor value is the associated movie
    adjacents = init_adjacents;
    parent = NULL;
    pathactor = "";
    pathmovie = "";
    visited = false;
    
}

