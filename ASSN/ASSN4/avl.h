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

    int max(int x, int y){ return (x>y)?(x):(y); }

    int _insert(Node *&target, int key) {
        int res = 0;
        if(target == NULL){
            target = new Node(key);
        } else if (key == target->key) {
            return 1;
        } else if (key < target->key){
            res = _insert(target->left, key);
        } else if (key > target->key) {
            res = _insert(target->right, key);
        }

        setHeight(_root);
        _balance(target);
        return res;
    }


    Node** getNodeByKey(int key) {
        return _getNodeByKey(&_root, key);
    }

    Node **_getNodeByKey(Node **_node, int key) {
        if((*_node) == nullptr) return nullptr;
        if((*_node)->key == key) return _node;

        Node** tmp_1 = nullptr;
        Node** tmp_2 = nullptr;
        if((*_node)->left != NULL) tmp_1 = _getNodeByKey(&((*_node)->left), key);
        if((*_node)->right != NULL) tmp_2 = _getNodeByKey(&((*_node)->right), key);

        if(tmp_1 != nullptr) return tmp_1;
        if(tmp_2 != nullptr) return tmp_2;

        return nullptr;
    }

    int setHeight(Node* target){
        if(target == nullptr){ return -1; }
        int left = (target->left != nullptr) ? (setHeight(target->left)) : (0);
        int right = (target->right != nullptr) ? (setHeight(target->right)) : (0);
        int _height = max(left, right) + 1;
        target->height = _height;
        return _height;
    }

    int getBf(Node* node){
        if(_root == nullptr) return -1;
        int left = node->left != nullptr ? node->left->height : 0;
        int right = node->right != nullptr ? node->right->height : 0;

        return left - right;
    }

    Node* rotate_right(Node* node){

        Node* tmp_right = new Node(node->key);
        tmp_right->right = node->right;

        node->right = tmp_right;

        node->key = node->left->key;

        Node* tmp_left = node->left;
        node->left = tmp_left->left;
        node->right->left = tmp_left->right;

        delete tmp_left;

        return node;
    }

    Node* rotate_left(Node* node){

        Node* tmp_left = new Node(node->key);
        tmp_left->left = node->left;

        node->left = tmp_left;

        node->key = node->right->key;

        Node* tmp_right = node->right;
        node->right = tmp_right->right;
        node->left->right = tmp_right->left;

        delete tmp_right;

        return node;
    }

    Node* rotate_right_left(Node* node){
        node->right= rotate_right(node->right);
        return rotate_left(node);

    }

    Node* rotate_left_right(Node* node){
        node->left= rotate_left(node->left);
        return rotate_right(node);
    }

    void balance(Node* target){
        if(target == NULL) { return; }

        balance(target -> left);
        balance(target -> right);

        _balance(target);
    }

    Node *_balance(Node *target) {
        int bf = getBf(target);
        int sub_bf;
        if(bf > 1){
            sub_bf = getBf(target->left);
            if(sub_bf < 0){
                rotate_left_right(target);
            } else {
                rotate_right(target);
            }
        } else if (bf < -1) {
            sub_bf = getBf(target->right);
            if(sub_bf > 0){
                rotate_right_left(target);
            } else {
                rotate_left(target);
            }
        }

        return target;
    }


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};