#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

class Pair
{
    public:
        stack<int> in_rows;
        stack<int> fixed_rows;

};



void printIntStack(stack<int> input)
{
    stack<int> in_stack = input;
    while(!in_stack.empty()){
        int top = in_stack.top();
        in_stack.pop();
        cout<<top<<" ";
    }
    cout<<endl;
    return;
}

bool validInsert(int row_to_insert, int size, stack<int> columns, stack<int> fixed_rows, bool neg_diags_open[], bool pos_diags_open[]){
    stack<int> c = columns;
    stack<int> r_flip = fixed_rows;
    stack<int> r;
    int r_top;
    while(!r_flip.empty()){
        r_top = r_flip.top();
        r_flip.pop();
        r.push(r_top);
    }
    bool NDO[size+size-1];
    bool PDO[size+size-1];
    for(int i=1; i<size+size;i++){
        if(neg_diags_open[i]==false){
        //    cout<<"neg diag closed on: "<<i<<endl;
            NDO[i]=false;
        }else{
            NDO[i]=true;
        }
        if(pos_diags_open[i]==false){
      //      cout<<"pos diag closed on: "<<i<<endl;
            PDO[i]=false;
        }else{
            PDO[i]=true;
        }

    }
    
    // cout<<"columns: ";
    // printIntStack(columns);
    // cout<<"fixed_rows: ";
    // printIntStack(fixed_rows);
    int neg_diag, pos_diag, row, col;

    
    while(!r.empty()){
        col = c.top();
        row = r.top();
    //    cout<<"col: "<<col<<" "<<"row: "<<row<<endl;
        c.pop();
        r.pop();
        neg_diag = col + row - 1;
        pos_diag = row - col + size;
    //    cout<<"neg_diag: "<<neg_diag<<" "<<"pos_diag: "<<pos_diag<<endl;
        NDO[neg_diag] = false;
        PDO[pos_diag] = false;
    }
    col = c.top();
    // cout<<"want to insert: " <<row_to_insert<<" at column: "<<col<<endl;
    row = row_to_insert;
    neg_diag = col + row - 1;
    pos_diag = row - col + size;
    // printIntStack(fixed_rows);
    // for(int i=1; i<size+size;i++){
    //     if(NDO[i]==false){
    //         cout<<"neg diag closed on: "<<i<<endl;
    //     }
    //     if(PDO[i]==false){
    //         cout<<"pos diag closed on: "<<i<<endl;
    //     }

    // }
    // cout<<"For row to INSERT neg_diag row: "<<neg_diag<<" "<<"pos_diag: "<<pos_diag<<endl;
    if(NDO[neg_diag]==true&&PDO[pos_diag]==true){
        // cout<<"valid"<<endl;
        // cout<<endl;
        return true;
    }else{
        // cout<<"invalid"<<endl;
        // cout<<endl;
        return false;
    }
    return false;

}

stack<int> findQueenRows(string input_str)
{
    
    char* com, *in_str, *nums;
    int size, col, row;
    stack<int> final_output;

    in_str = strdup(input_str.c_str());       //getting size of array
    com = strtok(in_str, " \t");
    size = atoi(com);
  
    int coordinates[size+1];
    bool neg_diags_open[size+size-1];
    bool pos_diags_open[size+size-1];
    bool row_open[size+1]; 
    bool col_open[size+1];         // indicates whether there is a queen placed on the column already
                                     // so that the row cannot be adjusted.
    int neg_diag, pos_diag;
    final_output.push(-1);

    // Initializing open rows, columns, and diagonals;
    int i;
    for(i=1; i<=size; i++){         
        coordinates[i]=0; 
        row_open[i]=true;
        col_open[i]=true;
    }
    int n = size+size-1;
    for(i=1; i<=n; i++){
        neg_diags_open[i]=true;
        pos_diags_open[i]=true;
    }

    nums = strtok(NULL, " ");
    // cout<<"INITIALIZING:"<<endl;
    while(nums!=NULL){                   //iterating over each number in line after size
        
        col = atoi(nums);
        nums = strtok(NULL, " ");
        
        row = atoi(nums);  
        if(row_open[row] == false || col_open[col] == false){ // checks that the initial horizontal and  
          return final_output;                                // vertical placement of queens is valid
        }                                                     // returns final_output[0]=-1 otherwise
        neg_diag = col + row - 1;
        pos_diag = row - col + size;
        if(neg_diags_open[neg_diag] == false || pos_diags_open[pos_diag] == false){ 
          return final_output;                               
        }     
        // cout<<"neg_diag: "<<neg_diag<<" "<<"pos_diag: "<<pos_diag<<endl;
        neg_diags_open[neg_diag] = false;
        pos_diags_open[pos_diag] = false;
        row_open[row] = false;
        col_open[col] = false;
        coordinates[col] = row;

        nums = strtok(NULL, " ");

    }
    // Generating all permutations of available rows (similar to allAnagrams in StackRecursion test)
    stack<stack<int>> row_permutation;
    stack<class Pair> recurStack;
    Pair stacktop, init;
    stack<int> temp, in_cols;
    for(i=1; i<=size; i++){ 
        if(col_open[i]==true){
            in_cols.push(i);
        }          
    }

    for(i=1; i<=size; i++){ 
        if(row_open[i]==true){
            init.in_rows.push(i);
        }          
    }

    recurStack.push(init);
    
    while(!recurStack.empty()){
        stacktop = recurStack.top();
        recurStack.pop();
        if(stacktop.in_rows.empty()){
            //printIntStack(stacktop.fixed_rows);
            row_permutation.push(stacktop.fixed_rows);
            //continue;
            break;
        }
        for(i=0; i<stacktop.in_rows.size(); i++){
            int first = stacktop.in_rows.top();
            //cout<<"next first: "<<first<<endl;
            //printIntStack(stacktop.in_rows);
            stacktop.in_rows.pop();
            //cout<<"stacktop.in_rows=";
            //printIntStack(stacktop.in_rows);
            if(validInsert(first, size, in_cols, stacktop.fixed_rows, neg_diags_open, pos_diags_open)){
                //cout<<endl<<endl;
                Pair to_push;
                to_push.in_rows = stacktop.in_rows;
                to_push.fixed_rows = stacktop.fixed_rows;
                to_push.fixed_rows.push(first);
                //  cout<<"valid in_rows: ";
                //  printIntStack(to_push.in_rows);
                //  cout<<"valid fixed_rows: ";
                //  printIntStack(to_push.fixed_rows);
                //  cout<<endl<<endl;
                recurStack.push(to_push);
            }
            int n;
            while(!stacktop.in_rows.empty()){
                n = stacktop.in_rows.top();
                stacktop.in_rows.pop();
                temp.push(n);
            }
            stacktop.in_rows.push(first);
            while(!temp.empty()){
                n = temp.top();
                temp.pop();
                stacktop.in_rows.push(n);
            }
        }

    }
    int r, c;
    stack<int> col_check;
    while(!in_cols.empty()){
        c = in_cols.top();
        in_cols.pop();
        col_check.push(c);

    }

    
     if(!row_permutation.empty()){
         final_output.pop();
        stack<int> perm = row_permutation.top();
        stack<int> col_perm = col_check;
        //  cout<<"columns: ";
        //  printIntStack(col_perm);
        //  cout<<"rows: ";
        //  printIntStack(perm);
        row_permutation.pop();
        
        while(!col_perm.empty()){
            c = col_perm.top();
            r = perm.top();
            col_perm.pop();
            perm.pop();
            coordinates[c]=r;


        }

         for(i=size; i>0; i--){
             final_output.push(coordinates[i]);
             final_output.push(i);
         }

        
     }

    
    // cout<<endl;

    return final_output;




}

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
    
    string in_str;
    while(getline(input, in_str)) // To get you all the lines.
    {
        stack<int> Queens = findQueenRows(in_str);
        while(!Queens.empty()){
            int r = Queens.top();
            if(r==-1){
                output<<"No solution";
                break;
            }else{
                output<<r<<" ";
            }
            Queens.pop();
            
        }
        output<<endl;
    }

    input.close();
    output.close();
    return 0;
}
