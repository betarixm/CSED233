#pragma once
#include "tree.h"

using namespace std;

class AVLTree: public BinaryTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insert(int key);
    int erase(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    int max(int x, int y);

    int _insert(Node *&target, int key);


    Node** getNodeByKey(int key);

    Node **_getNodeByKey(Node **_node, int key);

    int setHeight(Node* target);

    int getBf(Node* node);

    Node* rotate_right(Node* node);

    Node* rotate_left(Node* node);

    Node* rotate_right_left(Node* node);

    Node* rotate_left_right(Node* node);

    void balance(Node* target, int new_data);

    Node *_balance(Node *target);


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};