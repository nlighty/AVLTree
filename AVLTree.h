#ifndef AVL_BST_H
#define AVL_BST_H
#pragma once

#include <iostream>
#include "Node.h"

class AVLTree {
private:
    // --------------
    // Data members.
    // --------------

    // Root node.
    Node* root;

    // Number of dots.
    int numOfDots;

    // ----------
    // Methods.
    // ----------

    // Get the height of from a starting node.
    int Height(Node*);

    // Get the difference in height from the left and right sides of a node.
    int Difference(Node *);

    // Perform a right-right rotation.
    Node* RightRightRotate(Node *);

    // Perform a left-left rotation.
    Node* LeftLeftRotate(Node *);

    // Perform a right-left rotation.
    Node* LeftRightRotate(Node*);

    // Perform a left-right rotation.
    Node* RightLeftRotate(Node*);
    
    // Balance the tree.
    Node* Balance(Node*);

    // Insert new value into the tree.
    Node* Insert(Node*, std::string);

    // Show inorder.
    void Inorder(Node*);

    // Util function for printing in 2d.
    void Print2DUtil(Node*, int);

    // Returns true if hit, false otherwise.
    bool Filter(Node*, std::string);

    // Method for deallocating all memory used in the tree.
    void Deallocate(Node*);
public:
    // Default constructor.
    AVLTree();

    // Constructor with numOfDots passed in.
    AVLTree(int);

    // Destructor.
    ~AVLTree();

    // ---------
    // Methods.
    // ---------

    // Insert function.
    void Insert(std::string);

    // Inorder function.
    void Inorder();
    
    // Print 2d version of tree.
    void Print2D();

    // Filter out good domains.
    bool Filter(std::string);
};


#endif