#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int equalPathsHelper(Node * node) {
    // base clase: traversed to leaf node
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = equalPathsHelper(node -> left);
    int rightHeight = equalPathsHelper(node -> right);

    if (leftHeight != -1 && leftHeight == rightHeight || rightHeight == 0) {
        return leftHeight + 1;
    }
    else if (leftHeight == 0) {
        return rightHeight + 1;
    }

    return -1;
}


bool equalPaths(Node * root)
{
    // Add your code below
    if (root == nullptr) {
        return true;
    }

    int leftHeight = equalPathsHelper(root -> left);
    int rightHeight = equalPathsHelper(root -> right);

    if (leftHeight == -1 || rightHeight == -1) {
        return false;
    }

    if (root -> left == nullptr || root -> right == nullptr) {
        return true;
    }

    if (leftHeight == rightHeight) {
        return true;
    }

    return false;
    
}

