#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree: public BinaryTree {
public:
    BinarySearchTree() { };
    ~BinarySearchTree() { };

    int insert(int key);
    int erase(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    int _insert(Node*& target, int key);

    Node** getNodeByKey(int key);

    Node** _getNodeByKey(Node** _node, int key);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};