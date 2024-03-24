#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool equalPathsHelper(Node* node, int currHeight, int* leafHeight) {
    // first base case: traversed past nodes
    if (node == nullptr) {
        return true;
    }

    // second base case: traversed to leaf node
    if (node -> left == nullptr && node -> right == nullptr) {
        // set leafHeight to first traversed leaf's height
        if (leafHeight == nullptr) {
            *leafHeight = currHeight;
            return true;
        }
        
        // return true if current leaf's height matches first leaf's height
        if (currHeight == *leafHeight) {
            return true;
        }

        // return false if leaf heights dont match
        return false;
    }

    // recursive case: traverse to left and/or right child node
    return equalPathsHelper(node -> left, currHeight + 1, leafHeight) && equalPathsHelper(node -> right, currHeight + 1, leafHeight);
}


bool equalPaths(Node * root)
{
    // Add your code below
    return equalPathsHelper(root, 0, nullptr);    
}

