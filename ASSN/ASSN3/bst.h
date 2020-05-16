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
    Node** getNodeByKey(int key){
        return _getNodeByKey(&_root, key);
    }

    Node** _getNodeByKey(Node** _node, int key){
        if((*_node)->key == key) return _node;

        Node** tmp_1 = nullptr;
        Node** tmp_2 = nullptr;
        if((*_node)->left != NULL) tmp_1 = _getNodeByKey(&((*_node)->left), key);
        if((*_node)->right != NULL) tmp_2 = _getNodeByKey(&((*_node)->right), key);

        if(tmp_1 != nullptr) return tmp_1;
        if(tmp_2 != nullptr) return tmp_2;

        return nullptr;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};