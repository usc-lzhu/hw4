#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    int isBalancedHelper(Node<Key, Value>* node) const;
    void clearHelper(Node<Key, Value>* node);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return ((current_ == NULL && rhs.current_ == NULL) || (current_ -> getValue() == rhs -> second));
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (current_ == NULL && rhs.current_ == NULL) {
        return false;
    }
    
    if ((current_ == NULL && rhs.current_ != NULL) || (current_ != NULL && rhs.current_ == NULL)) {
        return true;
    }

    return (current_ -> getValue() != rhs -> second);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    std::cout << "\nstart operator++ function ------------------------------------" << std::endl;

    std::cout << "current before ++: " << current_ -> getKey() << std::endl;

    current_ = successor(current_);

    // std::cout << "current after ++: " << current_ -> getKey() << std::endl;
    if (current_ == NULL) {
        std::cout << "NULL" << std::endl;
    }

    std::cout << "end operator++ function --------------------------------------\n" << std::endl;


    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
     */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    
    std::cout << "begin: " << begin -> first << std::endl;

    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    if (curr != NULL) {
        std::cout << "curr: " << curr -> getKey() << std::endl;
    }
    else {
        std::cout << "not found" << std::endl;
    }
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    const Key& key = keyValuePair.first;
    const Value& value = keyValuePair.second;
    Node<Key, Value>* curr = root_;
    bool foundPos = false;

		printRoot(root_);
		std::cout << "\ninserting " << key << std::endl;
    
    // insert into empty tree
    if (empty()) {
        root_ = new Node<Key, Value>(key, value, NULL);
        // std::cout << "root after insert: " << root_ -> getKey() << std::endl;
				std::cout << "inserted " << root_ -> getKey() << std::endl;
        return;
    }

    // traverse through tree until leaf node
    while (!foundPos) {
				std::cout << "current: " << curr -> getKey() << std::endl; 

        // update value if key already exists
        if (key == curr -> getKey()) {
						std::cout << "here 0" << std::endl; 
            curr -> setValue(value);
						std::cout << "inserted " << curr -> getKey() << std::endl;
            foundPos = true;
        }
        // traverse left if key is less than current node
        else if (key < curr -> getKey()) {
						std::cout << "here 1" << std::endl; 

            if (curr -> getLeft() != NULL) {
                curr = curr -> getLeft();
								std::cout << "traverse left" << std::endl; 
            }
            else {
                foundPos = true;
                curr -> setLeft(new Node<Key, Value>(key, value, curr));
								std::cout << "inserted " << curr -> getLeft() -> getKey() << std::endl;
            }
        }
        // traverse right if key is greater than current node
        else {
						std::cout << "here 2" << std::endl; 
						
            if (curr -> getRight() != NULL) {
                curr = curr -> getRight();
								std::cout << "traverse right" << std::endl; 
            }
            else {
                foundPos = true;
                curr -> setRight(new Node<Key, Value>(key, value, curr));
								std::cout << "inserted " << curr -> getRight() -> getKey() << std::endl;
            }

        }
    }

    // std::cout << "root after insert: " << root_ -> getKey() << std::endl;

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    std::cout << "\nstart remove -----------------------------------------" << std::endl;

    
    Node<Key, Value>* curr = internalFind(key);

    // doesn't continue if key doesn't exist
    if (curr == NULL) {
        return;
    }
    
    std::cout << "curr: " << curr -> getKey() << std::endl;

    // swaps current node with its predecessor if current node has two children
    if (curr -> getLeft() != NULL && curr -> getRight() != NULL) {
        std::cout << "swap predecessor" << std::endl;

        // find predecessor
        Node<Key, Value>* pred = predecessor(curr);

        // swap current node and predecessor
        nodeSwap(curr, pred);
    }

    std::cout << "here 1" << std::endl;

    Node<Key, Value>* parent = curr -> getParent();
    Node<Key, Value>* child = NULL;

    std::cout << "parent: " << parent -> getKey() << std::endl;


    std::cout << "here 2" << std::endl;

    // sets child to left or right node if they exists
    if (curr -> getLeft() != NULL) {
        std::cout << "setting left child to null" << std::endl;
        child = curr -> getLeft();
    }
    else if (curr -> getRight() != NULL) {
        std::cout << "setting right child to null" << std::endl;
        child = curr -> getRight();
    }

    std::cout << "here 3" << std::endl;

    // update child's parent pointer if current node is not a leaf node
    if (child != NULL) {
        std::cout << "update parent pointer" << std::endl;
        child -> setParent(parent);
    }

    std::cout << "here 4" << std::endl;

    // update parent's left or right child pointer to current node's child 
    // pointer or NULL if current node is a leaf node
    if ((parent -> getLeft() != NULL) && (parent -> getLeft() -> getKey() == curr -> getKey())) {
        std::cout << "update parent's left child" << std::endl;
        parent -> setLeft(child);
    }
    else if ((parent -> getRight() != NULL) && (parent -> getRight() -> getKey() == curr -> getKey())) {
        std::cout << "update parent's right child" << std::endl;
        parent -> setRight(child);
    }

    std::cout << "here 5" << std::endl;

    // delete current node after updating pointers
    delete curr;

    std::cout << "here 6" << std::endl;

    
    std::cout << "end remove -------------------------------------------\n" << std::endl;


    // // curr has no children
    // if (curr -> getLeft() == NULL && curr -> getRight == NULL) {
    //     // curr is a left child
    //     if (parent -> getLeft() -> getKey == curr -> getKey) {
    //         parent -> setLeft(NULL);
    //     }
    //     // curr is a right child
    //     else {
    //         parent -> setRight(NULL);
    //     }
    // }
    // // curr has one child 
    // else {
    //     // curr has a left child
    //     if (curr -> getLeft() != NULL) {
    //         Node<Key, Value>* child = curr -> getLeft();
    //     }
    //     // curr has a right child
    //     else {
    //         Node<Key, Value>* child = curr -> getRight();
    //     }

    //     // curr is a left child
    //     if (parent -> getLeft() -> getKey == curr -> getKey) {
    //         parent -> setLeft(child);
    //     }
    //     // curr is a right child
    //     else {
    //         parent -> setRight(child);
    //     }
        
    //     child -> setParent(parent);
    // }

    // delete curr;

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    Node<Key, Value>* predecessor = NULL;

    // if left child exists, predecessor is right most node in left subtree
    if (current -> getLeft() != NULL) {
        predecessor = current -> getLeft();
        while (predecessor -> getRight() != NULL) {
            predecessor = predecessor -> getRight();
        }
    }
    // finds first parent node that has right child ancestor of current node
    else if (current -> getParent() != NULL) {
        Node<Key, Value>* parent = current -> getParent();
        predecessor = current;

        // loops while parent node has no right child or current node isn't a right child
        // in otherwords, stops looping when current node is parent's right child
        while (parent -> getRight() == NULL || parent -> getRight() -> getKey() != predecessor -> getKey()) {
            // breaks loop if traversed to root without finding the predecessor
            if (parent -> getParent() == NULL) {
                parent = NULL;
                break;
            }
            predecessor = parent;
            parent = parent -> getParent();
        }
        
        predecessor = parent;
    }

    return predecessor;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    std::cout << "start successor method ----------------------" << std::endl;
    std::cout << "current: " << current -> getKey() << std::endl;

    // TODO
    Node<Key, Value>* successor = NULL;

    std::cout << "here 1" << std::endl;

    // if right child exists, successor is left most node in left subtree
    if (current -> getRight() != NULL) {
        std::cout << "here 2" << std::endl;
        successor = current -> getRight();
        while (successor -> getLeft() != NULL) {
            successor = successor -> getLeft();
        }
    }
    // finds first parent node that has left child ancestor of current node
    else if (current -> getParent() != NULL) {
        std::cout << "here 3" << std::endl;
        Node<Key, Value>* parent = current -> getParent();
        successor = current;

        // loops while parent node has no left child or current node isn't a left child
        // in otherwords, stops looping when current node is parent's left child
        while (parent -> getLeft() == NULL || parent -> getLeft() -> getKey() != successor -> getKey()) {
            // breaks loop if traversed to root without finding the predecessor
            if (parent -> getParent() == NULL) {
                parent = NULL;
                break;
            }
            successor = parent;
            parent = parent -> getParent();
        }
        
        successor = parent;
    }
    
    std::cout << "end successor method ------------------------" << std::endl;


    return successor;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO

    clearHelper(root_);

    // iterator it = begin();
    // std::pair<const Key,Value>* curr = NULL;

    // while (it != end()) {
    //     *curr = *it;
    //     ++it;
    //     delete curr;
    // }

    // root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* node)
{
    if (node == NULL) {
        return;
    }

    clearHelper(node -> getLeft());
    clearHelper(node -> getRight());

    delete node;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (empty()) {
        return NULL;
    }

    Node<Key, Value>* smallestNode = root_; 

    while (smallestNode -> getLeft() != NULL) {
        smallestNode = smallestNode -> getLeft();
    }

    return smallestNode;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    std::cout << "\nstart internal find -----------------------------------------" << std::endl;
    // TODO
    // traverse through tree starting at the root
    Node<Key, Value>* curr = root_;

    while (curr != NULL) {
        if (curr -> getKey() == key) {
            std::cout << "found curr: " << curr -> getKey() << std::endl;
            std::cout << "end internal find -------------------------------------------" << std::endl;
            return curr;
        }
        else if (key < curr -> getKey()) {
            if (curr -> getLeft() == NULL) {
                break;
            }
            
            curr = curr -> getLeft();
        }
        else {
            if (curr -> getRight() == NULL) {
                break;
            }
            
            curr = curr -> getRight();
        }
    }
    std::cout << "did not find curr :(" << std::endl;
    std::cout << "end internal find -------------------------------------------\n" << std::endl;

    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if (isBalancedHelper(root_) == -1) {
        return false;
    }

    return true;    
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* node) const
{
    // base case: traversed to a leaf node
    if (node == NULL) {
        // returns that height is 0
        return 0;
    }

    // store left and right subtree's max height
    int leftHeight = isBalancedHelper(node -> getLeft());
    int rightHeight = isBalancedHelper(node -> getRight());

    // if either subtrees are unbalanced, return -1
    if (leftHeight == -1 || rightHeight == -1) {
        return -1;
    }

    // return if subtree heights are unbalanced or max subtree height
    if (leftHeight > rightHeight) {
        if (leftHeight - rightHeight > 1) {
            return -1;
        }
        
        return leftHeight + 1;
    }
    else {
        if (rightHeight - leftHeight > 1) {
            return -1;
        }
        
        return rightHeight + 1;    
    }

}




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
