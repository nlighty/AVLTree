#include "AVLTree.h"

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <sstream>

AVLTree::AVLTree() {
    root = NULL;
    numOfDots = 1;
}

AVLTree::AVLTree(int num_of_dots) {
    root = NULL;
    numOfDots = num_of_dots;
}

AVLTree::~AVLTree() {
    Deallocate(root);
}

int AVLTree::Height(Node* node) {
    // Initialize height variable.
    int height = 0;

    // If not at bottom.
    if(node != NULL) {
        // Grab the left side height.
        int leftHeight = Height(node->left);

        // Grab the right side height.
        int rightHeight = Height(node->right);

        // Height from the node is the max of both sides plus one.
        int maxHeight = std::max(leftHeight, rightHeight);
        height = maxHeight + 1;
    }

    // Return the height.
    return height;
}

int AVLTree::Difference(Node* node) {
    // Get the height of the left side.
    int leftHeight = Height(node->left);

    // Get the height of the right side.
    int rightHeight = Height(node->right);
    
    // Return the difference.
    return leftHeight - rightHeight;
}

Node* AVLTree::RightRightRotate(Node* parent_node) {
    // Initialize new node.
    Node* node;

    // Node is a copy of the parent's right child.
    node = parent_node->right;

    // Parent's right pointer now points to the node's left child.
    parent_node->right = node->left;

    // Node's left pointer now points to the parent node.
    node->left = parent_node;

    // Return the node.
    return node;
}

Node* AVLTree::LeftLeftRotate(Node* parent_node) {
    // Initialize new node.
    Node* node;

    // Node is copy of parent's left node.
    node = parent_node->left;

    // Parent's left pointer is now pointing to the new nodes right node.
    parent_node->left = node->right;
    
    // Node's right pointer now points to the parent node.
    node->right = parent_node;

    // Return the node.
    return node;
}


Node* AVLTree::LeftRightRotate(Node* parent_node) {
    // Initialize new node.
    Node* node;

    // Node is a copy of the parent node's left child.
    node = parent_node->left;

    // Perform a right-right rotation on the node and point the parent's left pointer to it.
    parent_node->left = RightRightRotate(node);

    // Perform a left-left rotation and return it.
    return LeftLeftRotate(parent_node);
}

Node* AVLTree::RightLeftRotate(Node* parent_node) {
    // Initialize new node.
    Node* node;

    // Node is a copy of the parent node's right child.
    node = parent_node->right;

    // Perform a left-left rotation on the node and point the parent's left pointer to it.
    parent_node->right = LeftLeftRotate(node);

    // Perform a right-right rotation and return it.
    return RightRightRotate(parent_node);
}


Node* AVLTree::Balance(Node* node) {
    // Grab the difference between left and right side heights of node.
    int balanceFactor = Difference(node);

    // If the difference is greater than 1 (left side is greater than right), 
    //  perform l-l or l-r rotation.
    // Else if the difference is less than -1 (right side is greater than left),
    //  perform r-l or r-r rotation. 
    if(balanceFactor > 1) {
        // If the left side has a greater left height, peform l-l rotation.
        // Else, perform l-r rotation.
        if(Difference(node->left) > 0) {
            node = LeftLeftRotate(node);
        } else {
            node = LeftRightRotate(node);
        }
    } else if (balanceFactor < -1) {
        // If the right side has a greater right height, perform r-l rotation.
        // Else, perform r-r rotation.
        if(Difference(node->right) > 0){
            node = RightLeftRotate(node);
        } else {
            node = RightRightRotate(node);
        }
    }

    // Return the node.
    return node;
}

Node* AVLTree::Insert(Node* node, std::string node_value) {
    // If node NULL (reached bottom), create new node with the value.
    // Else if the incoming value is less than the current node's value, insert left and balance.
    // Else if the incoming value is greater than or equal to the node's value, insert right and balance.
    if (node == NULL) {
        node = new Node(node_value);
    } else if (node_value < node->value) {
        node->left = Insert(node->left, node_value);
        node = Balance(node);
    } else if (node_value >= node->value) {
        node->right = Insert(node->right, node_value);
        node = Balance(node);
    }

    // Return the node. 
    return node;
}

void AVLTree::Insert(std::string node_value) {
    // If NULL, initialize root node with data.
    // Else, call insert function.
    if (root == NULL) {
        root = new Node(node_value);
    } else {
        root = Insert(root, node_value);
    }
}

void AVLTree::Inorder(Node* node) {
    // If bottom reached return.
    if(node == NULL) {
        return;
    }

    // Process left.
    Inorder(node->left);

    // Print node value.
    std::cout << node->value << " ";

    // Process right.
    Inorder(node->right);
}

void AVLTree::Inorder() {
    // Call inorder with root node.
    Inorder(root);
}


void AVLTree::Print2DUtil(Node *root, int space) { 
    // Base case 
    if (root == NULL) 
        return; 

    // Increase distance between levels 
    space += 3; 

    // Process right child first 
    Print2DUtil(root->right, space); 

    // Print current node after space 
    // count 
    std::cout<<std::endl; 
    for (int i = 3; i < space; i++) 
        std::cout<<" "; 
    std::cout<<root->value<<"\n"; 

    // Process left child 
    Print2DUtil(root->left, space); 
} 

// Wrapper over print2DUtil() 
void AVLTree::Print2D() 
{ 
    // Pass initial space count as 0 
    Print2DUtil(root, 0); 
}

// Filter function.
bool AVLTree::Filter(std::string value) {
    // Pass control to filter function with root node.
    return Filter(root, value);
}

// Filter function.
//   Returns true if value hits in the tree, false otherwise.
bool AVLTree::Filter(Node* node, std::string value) {
    // Return false if bottom of tree hit.
    if(node == NULL) {
        return false;
    }

    // If value is equal to node's value return true.
    // Else if value is less than node's value, continue down left side.
    // Else, continue down right side.
    if(value == node->value) {
        return true;
    } else if (value < node->value) {
        return Filter(node->left, value);
    } else {
        return Filter(node->right, value);
    }
}

void AVLTree::Deallocate(Node* node) {
    if(node == NULL) {
        return;
    }

    Deallocate(node->left);
    Deallocate(node->right);

    delete node;
}