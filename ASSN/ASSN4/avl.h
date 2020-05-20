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
        balance(target, key);
        return res;
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

    Node* rotate_LL(Node* node){

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

    Node* rotate_RR(Node* node){

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

    Node* rotate_RL(Node* node){

        Node* s1 = node->right;
        Node* s2 = s1->left;

        s2->right = s1;
        node->right = s2;
        s1->left = nullptr;

        return rotate_RR(node);

    }

    Node* rotate_LR(Node* node){
        Node* s1 = node->left;
        Node* s2 = s1->right;

        s2->left = s1;
        node->left = s2;
        s2->right = nullptr;

        return rotate_LL(node);
    }

    Node* balance(Node* target, int new_data){
        int bf = getBf(target);

        if(bf > 1){
            if(new_data < target -> left ->key){
                rotate_LL(target);
            } else if(new_data > target -> left ->key){
                rotate_LR(target);
            }
        } else if (bf < -1) {
            if(new_data < target -> right -> key){
                rotate_RL(target);
            } else if (new_data > target -> right -> key){
                rotate_RR(target);
            }
        }

        return target;
    }


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};