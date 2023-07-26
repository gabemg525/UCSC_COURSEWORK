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




bool checkQueens(int size, vector<int> rows_to_check)
{
  
    bool spaces[size+1][size+1];
    for(int x = 1; x <= size; x++){
         for(int y = 1; y <= size; y++){
             spaces[x][y] = true;
             
         }
         
    }
//      for(int i = 1; i<=size; i++){
//           cout<<" ("<<i<<","<<rows_to_check[i]<<")\n";
         
//      }
//    cout<<endl;
    int x, y;
     for(int i=1; i<=size; i++){
         for(int d=1; d<=size; d++){
             x = i-d;
             y = rows_to_check[i]-d;
             if(x>0 && y>0){
                 spaces[x][y] = false;
             }
             x = i+d;
             y = rows_to_check[i]+d;
             if(x<=size && y<=size){
                 spaces[x][y] = false;
             }
             x = i-d;
             y = rows_to_check[i]+d;
             if(x>0 && y<=size){
                 spaces[x][y] = false;
             }
             x = i+d;
             y = rows_to_check[i]-d;
             if(x<=size && y>0){
                 spaces[x][y] = false;
             }
         }
     }
/*test code for printing board*/
//      for(int i = 1; i<=size; i++){           
//        for(int j = 1; j<=size; j++){
//          cout<<" ("<<i<<","<<j<<")";
//          if(spaces[i][j]==false){
//            cout<<"F ";
//          }else{
//            cout<<"T ";
//          }
//         }
//         cout<<endl;
     
//       }
    
    for(int i = 1; i<=size; i++){
          
         if(spaces[i][rows_to_check[i]]==false){

           return false;
         }
    }
    return true;
}

vector<int> findQueens(string input_str)
{
    
    char* S, *in_str, *nums;
    int size, col, row;
    vector<int> final_output;


    
  
  
    in_str = strdup(input_str.c_str());       //getting size of array
    S = strtok(in_str, " \t");
    size = atoi(S);
  
    int coordinates[size+1];
    bool fixed_row[size+1]; 
    bool fixed_col[size+1];         // indicates whether there is a queen placed on the column already
                                     // so that the row cannot be adjusted.
    final_output.push_back(-1);
    for(int i=1; i<=size; i++){
         coordinates[i]=0; 
         fixed_row[i]=false;
         fixed_col[i]=false;

     }
     
    
    
    nums = strtok(NULL, " ");

    while(nums!=NULL){                   //iterating over each number in line after size
        
        col = atoi(nums);
        nums = strtok(NULL, " ");
        
        row = atoi(nums);  
        if(fixed_row[col] == true || fixed_col[row] == true){ // checks that the initial horizontal and  
          return final_output;                                // vertical placement of queens is valid
        }                                                     // returns final_output[0]=-1 otherwise
        coordinates[col] = row;
        fixed_row[col] = true;
        fixed_col[row] = true;

        nums = strtok(NULL, " ");

     }
       
        vector<int> permutation; 
        
        for(int i=1; i<=size; i++){ 
            if(!fixed_col[i]==true){              // push_back()'s to permutation vector will skip over
                permutation.push_back(i);         // fixed columns
                
            }
            
        }
//         for(int i=0; i<7; i++){
//               cout<<" ("<<i+1<<","<<permutation[i]<<")";
//            } 
 
        do{
           vector<int> rows_to_check;
           int p=0;
           rows_to_check.push_back(0);
           for(int i=1; i<=size ;i++ ){           //setting row_to_check
               if(fixed_row[i]==true){
                    rows_to_check.push_back(coordinates[i]);
                }else{
                    rows_to_check.push_back(permutation[p]);
                    p++;
                }
           } 
           

           if(checkQueens(size, rows_to_check)==true){
               final_output = rows_to_check;
               break;
           }
 //          cout<<endl;
        }while(next_permutation(permutation.begin(), permutation.end()));

  
    
    
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
    
      
    
    string in_str; // to store the input string from the file
    while(getline(input, in_str)){
         vector<int> Queens = findQueens(in_str); 
          if(Queens[0]==-1){
            output<<"No solution";
          }
          
          for(unsigned int i = 1; i<Queens.size() ;i++){
             output<<i<<" "<<Queens[i]<<" ";
          }
         output<<endl;

        
    }
    

    
    
    input.close();
    output.close();
    return 0;
}