// Filename: bst.cpp
// 
// Contains the class BST that represents a binary search tree. This contains some basic operations, such as insert, delete, find, and printing in various traversal orders
// 
// C. Seshadhri, Jan 2020

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

// Default constructor sets head and tail to null
BST :: BST()
{
	root = NULL;
}

// Insert(int val): Inserts the int val into tree, at the head of the list. Note that there may be multiple copies of val in the list. Just calls the recursive function
// Input: Int to insert into the BST
// Output: Void, just inserts new Node
void BST :: insert(int val)
{
    Node *to_insert = new Node(val); // create a new Node with the value val
    if (root == NULL) // tree is currently empty
        root = to_insert; // make new node the root
    else
        insert(root,to_insert); // make call to recursive insert, starting from root
}

// insert(Node* start, Node* to_insert): Inserts the Node to_insert into tree rooted at start. We will always call with start being non-null. Note that there may be multiple copies of val in the list. 
// Input: Int to insert into the subtree
// Output: Void, just inserts new Node
void BST :: insert(Node* start, Node* to_insert)
{
    if (start == NULL) // in general, this should not happen. We never call insert from a null tree
        return;
    if (to_insert->key <= start->key) // inserted node has smaller (or equal) key, so go left
    {
        if(start->left == NULL)
        {
            start->left = to_insert; // make this node the left child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->left, to_insert);
            return;
        }
    }
    else // inserted node has larger key, so go right
    {
        if(start->right == NULL)
        {
            start->right = to_insert; // make this node the right child
            to_insert->parent = start; // set the parent pointer
            return;
        }
        else // need to make recursive call
        {
            insert(start->right, to_insert);
            return;
        }
    }
}

// find(int val): Finds a Node with key "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node* BST :: find(int val)
{
    return find(root, val); // call the recursive function starting at root
}

// find(Node* start, int val): Recursively tries to find a Node with key "val", in subtree rooted at val
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node* BST :: find(Node* start, int val)
{
    if (start == NULL || start->key == val) // tree is empty or we found val
        return start;
    if(val < start->key) // val is smaller, so go left
        return find(start->left, val);
    else // val is larger, so go right
        return find(start->right, val);
}

// minNode(Node* start): gets the minimum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the minimum node in the subtree
Node* BST :: minNode(Node* start)
{
    if(start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if(start->left == NULL) // Base case: we have found the minimum
        return start;
    else
        return minNode(start->left); // recursive call in left subtree
}

// maxNode(Node* start): gets the maximum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the maximum node in the subtree
Node* BST :: maxNode(Node* start)
{
    if(start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if(start->right == NULL) // Base case: we have found the maximum
        return start;
    else
        return maxNode(start->right); // recursive call in left subtree
}

// deleteNode(int val): Delete a Node with key val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* BST :: deleteKey(int val)
{
    return deleteNode(find(val)); // get a node with the value and delete that node
}

// deleteNode(Node* to_delete): Delete the input node, and return pointer to the deleted node. The node will be isolated from the tree, to prevent memory leaks
// Input: Node to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. 
Node* BST :: deleteNode(Node* to_delete)
{
    if(to_delete == NULL) // val not present in tree, so return NULL
        return NULL;

    bool isRoot = (to_delete == root) ? true : false; // determine if node to delete is root
    bool isLeftChild = false;
    if (!isRoot) // if this is not the root
        isLeftChild = (to_delete->parent->left == to_delete) ? true : false; // determine if node is left child of parent. Note that line throws error iff to_delete is root

    bool isDeleted = false; // convenient flag for writing code
    
    // if to_delete's left child is NULL, then we can splice this node off. We set the appropriate
    // pointer of the parent to the right child of to_delete
    if(to_delete->left == NULL)
    {
        if(isRoot) // if deleting root, then we reset root
        {
            root = to_delete->right;
            if(root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if(isLeftChild) // node is left child of parent
                to_delete->parent->left = to_delete->right; // setting left child of parent to be right child of node
            else // node is right child of parent
                to_delete->parent->right = to_delete->right; // setting right child of parent to be right child of node
            if(to_delete->right != NULL) // to_delete is not a leaf
                to_delete->right->parent = to_delete->parent; // update parent of the child of the deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    // suppose node is not deleted yet, and it's right child is NULL. We splice off as before, by setting parent's child pointer to to_delete->left
    if(!isDeleted && to_delete->right == NULL) 
    {
        if(isRoot) // if deleting root, then we reset root
        {
            root = to_delete->left;
            if(root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if(isLeftChild) // node is left child of parent
                to_delete->parent->left = to_delete->left; // setting left child of parent to be left child of node
            else // node is right child of parent
                to_delete->parent->right = to_delete->left; // setting right child of parent to be left child of node
            if(to_delete->left != NULL) // to delete is not a leaf
                to_delete->left->parent = to_delete->parent; // update parent of the child of deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    if(isDeleted) // so node has been deleted
    {
        to_delete->left = to_delete->right = NULL;
        return to_delete;
    }
    
    // phew. The splicing case is done, so now for the recursive case. Both children of to_delete are not null, so we replace the data in to_delete by the successor. Then we delete the successor node
    // first, get the minimum node of right subtree
    Node* succ = minNode(to_delete->right);
    to_delete->key = succ->key;
//     cout << "Replacing with "+to_string(succ->key) << endl;
    return deleteNode(succ); // make recursive call on succ. Note that succ has one null child, so this recursive call will terminate without any other recursive calls
}


// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void BST :: deleteBST()
{
    deleteBST(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void BST :: deleteBST(Node* start)
{
    if(start == NULL) // tree is already empty
        return; 
    deleteBST(start->left); // delete left subtree
    deleteBST(start->right); // delete right subtree
    delete(start); // delete node itself
}

// Prints tree in order. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree in order
string BST :: printInOrder()
{
    return printInOrder(root);
}

// Prints tree Preorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree pre order
string BST :: printPreOrder()
{
    return printPreOrder(root);
}

// Prints tree Postorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree post order
string BST :: printPostOrder()
{
    return printPostOrder(root);
}
    
// Prints rooted subtree tree in order, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in order
string BST :: printInOrder(Node* start)    
{
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printInOrder(start->left);
    string rightpart = printInOrder(start->right);
    string output = to_string(start->key);
    if(leftpart.length() != 0) // left part is empty
        output = leftpart + " " + output; // append left part
    if(rightpart.length() != 0) // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}
    
// Prints rooted subtree tree preorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree preorder
string BST :: printPreOrder(Node* start)    
{
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
    string output = to_string(start->key);
    if(leftpart.length() != 0) // left part is empty
        output = output + " " + leftpart; // append left part
    if(rightpart.length() != 0) // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}

// Prints rooted subtree tree postorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in post order
string BST :: printPostOrder(Node* start)    
{
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPostOrder(start->left);
    string rightpart = printPostOrder(start->right);
    string output = to_string(start->key);
    if(rightpart.length() != 0) // right part is empty
        output = rightpart+" "+output; // append left part
    if(leftpart.length() != 0) // left part in empty
        output = leftpart+" "+output; // append right part
    return output;
}

// Node* BST :: lca(Node* root, int val1, int val2)
// {
//     if (root == NULL){
//         return NULL;
//     } 

//     if (root->key > val1 && root->key > val2){
//         return lca(root->left, val1, val2);
//     } 

//     if (root->key < val1 && root->key < val2){
//         return lca(root->right, val1, val2);
//     }
//     return root;
// }


// Node* BST :: lca(int val1, int val2)
// {
//     if(find(val1)!=NULL&&find(val2)!=NULL){
//         return lca(root, val1, val2);
//     }
//     else{
//         return NULL;
//     }

    
// }
// Node* BST :: lca(Node* start, int val1, int val2)
// {
//     if(start->key>=val1&&start->key<=val2||start->key<=val1&&start->key>=val2){
//         return start;
//     }
//     if(start->key<val1&&start->key<val2){
//         return lca(start->right, val1, val2);
//     }
//     if(start->key>val1&&start->key>val2){
//         return lca(start->left, val1, val2);
//     }
// }

Node* BST :: lca(int val1, int val2)
{

    if(find(val1)==NULL||find(val2)==NULL){
        return NULL;
    }
    Node*curr=root;
    while(!(curr->key>=val1&&curr->key<=val2||curr->key<=val1&&curr->key>=val2)){

        if(curr->key>val1&&curr->key>val2){
            curr=curr->left;
        }
        if(curr->key<val1&&curr->key<val2){
            curr=curr->right;
        }
    }
    return curr;


    // if(find(val1)==NULL||find(val2)==NULL){
    //     return NULL;
    // }
    
    // Node* curr = root;
    // while(curr!=NULL){
    //     if(curr->key<=val1&&curr->key>=val2||curr->key>=val1&&curr->key<=val2){
    //         return curr;
    //     }
    //     if(curr->key<val1&&curr->key<val2){
    //         curr=curr->right;
    //     }
    //     if(curr->key>val1&&curr->key>val2){
    //         curr=curr->left;
    //     }
    // }
    // return NULL;
}
// 5 min

int BST :: width(int h)
{
    if(!root) return 0;
    int currH = 1, currW = 1, maxW = 1;
    Node* temp = root;
    stack<Node*> recurStack, tempStack;
    recurStack.push(temp);
    while(!recurStack.empty()&&currH<h){
        currW=0;
        while(!recurStack.empty()){
            temp = recurStack.top();
            if(temp->left) tempStack.push(temp->left);
            if(temp->right) tempStack.push(temp->right);
            recurStack.pop();
        }
        while(!tempStack.empty()){
            recurStack.push(tempStack.top());
            tempStack.pop();
            currW++;
        }
        if(currW>maxW){
            maxW=currW;
        }
        currH++;
    }
    return maxW;





    // if(!root) return 0;
    // stack<Node*> recurStack, tempStack;
    // int currW = 1;
    // int maxW = 1;
    // int currH = 1;
    // Node* temp = root;
    // recurStack.push(temp);
    // while(!recurStack.empty()&&currH<h)
    // {
        
    //     currW=0;
    //     while(!recurStack.empty()){
    //         temp=recurStack.top();
    //         if(temp->left){
    //             tempStack.push(temp->left);
    //         }
    //         if(temp->right){
    //             tempStack.push(temp->right);
    //         }
    //         recurStack.pop();
    //     }
    //     while(!tempStack.empty()){
    //         recurStack.push(tempStack.top());
    //         currW++;
    //         tempStack.pop();
    //     }
    //     if(currW>maxW){
    //         maxW=currW;
    //     }
    //     currH++;
    // }
    // return maxW;

}




string BST :: path(int val1, int val2)
{
    if(find(val1)==NULL||find(val2==NULL)){
        return "";
    }
    string final_out = "";
    int L = lca(val1, val2)->key;
    Node* temp = find(val1);
    while(temp->key!=L){
        final_out=final_out+'U';
        temp=temp->parent;
    }
    while(temp->key!=val2){
        if(temp->key<val2){
            temp=temp->right;
            final_out=final_out+'R';
        }
        if(temp->key>val2){
            temp=temp->left;
            final_out=final_out+'L';
        }
    }
    return final_out;


}


void BST :: printLevelOrder(Node* start, string* output, int height)
{
    if(start==NULL){
        return;
    }
    if(height==1){
        *output=*output+to_string(start->key)+" ";
    }else if(height>1){
        printLevelOrder(start->left, output, height-1);
        printLevelOrder(start->right, output, height-1);
    } 
}

string BST :: printLevelOrder()

{
    int h = height(root);
    string output = "";
    string *ptr = &output;
    for(int i=1;i<=h;i++){
        printLevelOrder(root,ptr,i);
    }
    return output;
}

int BST :: height(Node* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}

string BST :: printLevelOrder2(){
    int h = height(root);
    string level[h+1];
    OrderEachLevel(root, level, 1);
    string output="";
    for(int i=1; i<=h; i++){
        output+=level[i];
    }
    return output;

}

void BST :: OrderEachLevel(Node* start, string level[], int height){
    if(start==NULL){
        return;
    }else{
        level[height]=level[height]+to_string(start->key)+" ";
    }
    OrderEachLevel(start->left, level, height+1);
    OrderEachLevel(start->right, level, height+1);
}

// Given the preorder traversal of a BST, reconstruct the tree.

Node* BST :: preReconstruct()
{
    return root;
}

// Check if two BSTs are identical.

bool BST :: isIdentical(Node* root1, Node* root2)
{
    // Check if both the trees are empty
    if (root1 == NULL && root2 == NULL)
        return true;
    // If any one of the tree is non-empty
    // and other is empty, return false
    else if (root1 == NULL || root2 == NULL)
        return false;
    else { // Check if current data of both trees equal
        // and recursively check for left and right subtrees
        if (root1->key == root2->key && isIdentical(root1->left, root2->left)
            && isIdentical(root1->right, root2->right))
            return true;
        else
            return false;
    }
}

// Given a value val, delete all nodes in the tree less than val. Try to do
// this without visiting all the nodes less than val.

void BST :: deleteLessThan(int val)
{
    Node* N = find(val);
    N->left=NULL;

    return;
}

