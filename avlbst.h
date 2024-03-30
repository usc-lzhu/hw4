#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node, bool nIsLeftChild);
    void removeFix(AVLNode<Key, Value>* node, int diff);
    virtual void rotateRight(AVLNode<Key, Value>* node);
    virtual void rotateLeft(AVLNode<Key, Value>* node);



};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
    // exit if rotation isn't possible
    if (node == NULL || node -> getLeft() == NULL) {
        return;
    }
    // std::cout << "\n\nrotateRight start ---------------------------------------" << std::endl;
    // this -> print();    

    AVLNode<Key, Value>* parent = node -> getParent();
    AVLNode<Key, Value>* child = node -> getLeft();
    AVLNode<Key, Value>* grandchild = child -> getRight();

    // update parent's child pointer if parent isn't null
    if (parent != NULL) {
        // update parent's left child if left child's key matches current node's key
        if ((parent -> getLeft() != NULL) && (parent -> getLeft() -> getKey() == node -> getKey())) {
            parent -> setLeft(child);
        }
        // update parent's right child
        else if (parent -> getRight() != NULL) {
            parent -> setRight(child);
        }
    }
    // update root of tree if parent is null
    else {
        this -> root_ = child;
    }

    // update pointers and balances
    child -> setParent(parent);
    child -> setRight(node);

    node -> setParent(child);
    node -> setLeft(grandchild);

    if (grandchild != NULL) {
        grandchild -> setParent(node);
    }

    // this -> print();
    // std::cout << "rotateRight end -----------------------------------------\n\n" << std::endl;

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
    // exit if rotation isn't possible
    if (node == NULL || node -> getRight() == NULL) {
        return;
    }

    // std::cout << "\n\nrotateLeft start ---------------------------------------" << std::endl;
    // this -> print();

    AVLNode<Key, Value>* parent = node -> getParent();
    AVLNode<Key, Value>* child = node -> getRight();
    AVLNode<Key, Value>* grandchild = child -> getLeft();

    // update parent's child pointer if parent isn't null
    if (parent != NULL) {
        // update parent's left child if left child's key matches current node's key
        if ((parent -> getLeft() != NULL) && (parent -> getLeft() -> getKey() == node -> getKey())) {
            parent -> setLeft(child);
        }
        // update parent's right child
        else if (parent -> getRight() != NULL) {
            parent -> setRight(child);
        }
    }
    // update root of tree if parent is null
    else {
        this -> root_ = child;
    }

    // update pointers and balances
    child -> setParent(parent);
    child -> setLeft(node);

    node -> setParent(child);
    node -> setRight(grandchild);
    
    if (grandchild != NULL) {
        grandchild -> setParent(node);
    }

    // this -> print();
    // std::cout << "rotateLeft end -----------------------------------------\n\n" << std::endl;
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO

    const Key& key = new_item.first;
    const Value& value = new_item.second;
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this -> root_);

    // insert into empty tree
    if (this -> empty()) {
        this -> root_ = new AVLNode<Key, Value>(key, value, NULL);
		// std::cout << "inserted " << this -> root_ -> getKey() << std::endl;
        return;
    }

    bool isLeftChild = false;

    // traverse through tree until leaf node
    while (curr != NULL) {
		// std::cout << "current: " << curr -> getKey() << std::endl; 

        // update value if key already exists
        if (key == curr -> getKey()) {
            curr -> setValue(value);
            return;
        }
        // traverse left if key is less than current node
        else if (key < curr -> getKey()) {
            if (curr -> getLeft() != NULL) {
                curr = curr -> getLeft();
            }
            else {
                curr -> setLeft(new AVLNode<Key, Value>(key, value, curr));
                isLeftChild = true;
                break;
            }
        }
        // traverse right if key is greater than current node
        else {
            if (curr -> getRight() != NULL) {
                curr = curr -> getRight();
            }
            else {
                curr -> setRight(new AVLNode<Key, Value>(key, value, curr));
                isLeftChild = false;
                break;
            }
        }
    }

    // fix balance if parent's initial balance was 0 
    if (curr -> getBalance() == 0) {
        if (isLeftChild) {
            curr -> setBalance(-1);
            insertFix(curr, curr -> getLeft(), true);
        }
        else {
            curr -> setBalance(1);
            insertFix(curr, curr -> getRight(), false);
        }
    }
    else {
        curr -> setBalance(0);
    }


}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node, bool nIsLeftChild) {
    std::cout << "fixing " << node -> getKey() << std::endl;
    
    if (parent == NULL || parent -> getParent() == NULL) {
        return;
    }

    AVLNode<Key, Value>* grandparent = parent -> getParent();
    bool pIsLeftChild;
    int gBalance;

    if ((grandparent -> getLeft() != NULL) && (grandparent -> getLeft() -> getKey() == parent -> getKey())) {
        pIsLeftChild = true;
    }
    else {
        pIsLeftChild = false;
    }

    std::cout << "child is a left child: " << nIsLeftChild << std::endl;
    std::cout << "parent is a left child: " << pIsLeftChild << std::endl;

    // parent is a left child
    if (pIsLeftChild) {
        gBalance = grandparent -> getBalance() - 1;
        grandparent -> setBalance(gBalance);

        if (gBalance == 0) {
            return;
        }
        else if (gBalance == -1) {
            insertFix(grandparent, parent, pIsLeftChild);
        }
        else if (gBalance == -2) {
            // parent is a left child and node is a left child
            // zig-zig case
            if (nIsLeftChild == true) {
                rotateRight(grandparent);
                parent -> setBalance(0);
                grandparent -> setBalance(0);
            }
            // parent is a left child and node is a right child
            // zig-zag case
            else {
                rotateLeft(parent);
                rotateRight(grandparent);

                if (node -> getBalance() == -1) {
                    parent -> setBalance(0);
                    grandparent -> setBalance(1);
                    node -> setBalance(0);
                }
                else if (node -> getBalance() == 0) {
                    parent -> setBalance(0);
                    grandparent -> setBalance(0);
                    node -> setBalance(0);
                }
                else if (node -> getBalance() == 1) {
                    parent -> setBalance(-1);
                    grandparent -> setBalance(0);
                    node -> setBalance(0);
                }
            }
        }
    }
    // parent is a right child
    else {
        gBalance = grandparent -> getBalance() + 1;
        grandparent -> setBalance(gBalance);

        if (gBalance == 0) {
            return;
        }
        else if (gBalance == 1) {
            insertFix(grandparent, parent, pIsLeftChild);
        }
        else if (gBalance == 2) {
            // parent is a right child and node is a right child
            // zig-zig case
            if (nIsLeftChild == false) {
                rotateLeft(grandparent);
                parent -> setBalance(0);
                grandparent -> setBalance(0);
            }
            // parent is a right child and node is a left child
            // zig-zag case
            else {
                rotateRight(parent);
                rotateLeft(grandparent);

                if (node -> getBalance() == 1) {
                    parent -> setBalance(0);
                    grandparent -> setBalance(-1);
                    node -> setBalance(0);
                }
                else if (node -> getBalance() == 0) {
                    parent -> setBalance(0);
                    grandparent -> setBalance(0);
                    node -> setBalance(0);
                }
                else if (node -> getBalance() == -1) {
                    parent -> setBalance(1);
                    grandparent -> setBalance(0);
                    node -> setBalance(0);
                }
            }
        }
    }
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this -> internalFind(key));

    // doesn't continue if key doesn't exist
    if (curr == NULL) {
        return;
    }
    
    // std::cout << "curr: " << curr -> getKey() << std::endl;

    // swaps current node with its predecessor if current node has two children
    if (curr -> getLeft() != NULL && curr -> getRight() != NULL) {
        // std::cout << "swap predecessor" << std::endl;

        // find predecessor
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this -> predecessor(curr));

        // swap current node and predecessor
        nodeSwap(curr, pred);
    }

    AVLNode<Key, Value>* parent = curr -> getParent();
    AVLNode<Key, Value>* child = NULL;
    int diff = 0;

    // sets child to left or right node if they exists
    if (curr -> getLeft() != NULL) {
        // std::cout << "set left child" << std::endl;
        child = curr -> getLeft();
    }
    else if (curr -> getRight() != NULL) {
        // std::cout << "set right child" << std::endl;
        child = curr -> getRight();
    }

    // update child's parent pointer if current node is not a leaf node
    if (child != NULL) {
        // std::cout << "update child's parent pointer" << std::endl;
        child -> setParent(parent);
    }

    // update parent's left or right child pointer to current node's child 
    // pointer or NULL if current node is a leaf node
    if (parent == NULL) {
        if (child == NULL) {
            this -> root_ = NULL;
        } 
        else {
            this -> root_ = child;
        }
    }
    else if ((parent -> getLeft() != NULL) && (parent -> getLeft() -> getKey() == curr -> getKey())) {
        // std::cout << "update parent's left child" << std::endl;
        diff = 1;
        parent -> setLeft(child);
        // parent -> setBalance(parent -> getBalance() + diff);
    }
    else if ((parent -> getRight() != NULL) && (parent -> getRight() -> getKey() == curr -> getKey())) {
        // std::cout << "update parent's right child" << std::endl;
        diff = -1;
        parent -> setRight(child);
        // parent -> setBalance(parent -> getBalance() + diff);
    }

    // delete current node after updating pointers
    delete curr;

    // if (parent != NULL) std::cout << "parent balance in remove function: " << (int16_t)(parent -> getBalance()) << std::endl;
    // fix balance after removal
    removeFix(parent, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff) {
    // exit if node is null
    if (node == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = node -> getParent();
    int ndiff = 0;

    if (parent != NULL) {
        // node is a left child
        if ((parent -> getLeft() != NULL) && (parent -> getLeft() -> getKey() == node -> getKey())) {
            ndiff = 1;
        }
        // node is a right child
        else {
            ndiff = -1;
        }
    }

    if (diff == -1) {
        // std::cout << "here ////////////////////////////////////////////" << std::endl;
        // std::cout << "node balance: " << (int16_t)(node -> getBalance()) << std::endl;
        if (node -> getBalance() + diff == -2) {
            // std::cout << "here -2 /////////////////////////////////////////////" << std::endl;
            AVLNode<Key, Value>* child = node -> getLeft();

            // zig-zig case
            if (child -> getBalance() == -1) {
                rotateRight(node);
                node -> setBalance(0);
                child -> setBalance(0);
                removeFix(parent, ndiff);
            }
            // zig-zig case
            else if (child -> getBalance() == 0) {
                rotateRight(node);
                node -> setBalance(-1);
                child -> setBalance(1);
            }
            // zig-zag case
            else if (child -> getBalance() == 1) {
                AVLNode<Key, Value>* grandchild = child -> getRight();
                rotateLeft(child);
                rotateRight(node);
                
                if (grandchild -> getBalance() == 1) {
                    node -> setBalance(0);
                    child -> setBalance(-1);
                    grandchild -> setBalance(0);
                }
                else if (grandchild -> getBalance() == 0) {
                    node -> setBalance(0);
                    child -> setBalance(0);
                    grandchild -> setBalance(0);
                }
                else if (grandchild -> getBalance() == -1) {
                    node -> setBalance(1);
                    child -> setBalance(0);
                    grandchild -> setBalance(0);
                }

                removeFix(parent, ndiff);
            }
        }
        else if (node -> getBalance() + diff == -1) {
            // std::cout << "here -1 /////////////////////////////////////////////" << std::endl;
            node -> setBalance(-1);
        }
        else if (node -> getBalance() + diff == 0) {
            // std::cout << "here 0////////////////////////////////////////////" << std::endl;
            node -> setBalance(0);
            removeFix(parent, ndiff);
        }
    }
    else {
        if (node -> getBalance() + diff == 2) {
            AVLNode<Key, Value>* child = node -> getRight();

            // zig-zig case
            if (child -> getBalance() == 1) {
                rotateLeft(node);
                node -> setBalance(0);
                child -> setBalance(0);
                removeFix(parent, ndiff);
            }
            // zig-zig case
            else if (child -> getBalance() == 0) {
                rotateLeft(node);
                node -> setBalance(1);
                child -> setBalance(-1);
            }
            // zig-zag case
            else if (child -> getBalance() == -1) {
                AVLNode<Key, Value>* grandchild = child -> getLeft();
                rotateRight(child);
                rotateLeft(node);
                
                if (grandchild -> getBalance() == -1) {
                    node -> setBalance(0);
                    child -> setBalance(1);
                    grandchild -> setBalance(0);
                }
                else if (grandchild -> getBalance() == 0) {
                    node -> setBalance(0);
                    child -> setBalance(0);
                    grandchild -> setBalance(0);
                }
                else if (grandchild -> getBalance() == 1) {
                    node -> setBalance(-1);
                    child -> setBalance(0);
                    grandchild -> setBalance(0);
                }

                removeFix(parent, ndiff);
            }
        }
        else if (node -> getBalance() + diff == 1) {
            node -> setBalance(1);
        }
        else if (node -> getBalance() + diff == 0) {
            node -> setBalance(0);
            removeFix(parent, ndiff);
        }
    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
