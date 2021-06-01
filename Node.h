#ifndef NODE_H
#define NODE_H
#pragma once

#include <iostream>

class Node {
private:
    std::string value;
    Node* left;
    Node* right;
public:
    Node(){
        value = "";
        left = NULL;
        right = NULL;
    }

    Node(std::string node_value) {
        value = node_value;
        left = NULL;
        right = NULL;
    }

    friend class AVLTree;
};


#endif