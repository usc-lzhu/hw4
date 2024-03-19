#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int equalPathsHelper(Node * node) {
    // base clase: traversed past leaf node
    if (node == nullptr) {
        return 0;
    }

    if (equalPathsHelper(node -> left) == equalPathsHelper(node -> right)) {
        return 1;
    }
}


bool equalPaths(Node * root)
{
    // Add your code below

    if (equalPathsHelper(root)) {
        return true;
    }

    return false;
    
}

