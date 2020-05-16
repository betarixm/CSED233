#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return _insert(_root, key);

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node** target = getNodeByKey(key);
    if(target == nullptr){ return 1; }

    if((*target)->left == NULL && (*target)->right == NULL){
        delete *target;
        *target = NULL;
    } else if ((*target)->left != NULL && (*target)->right != NULL){
        Node** tmp = &((*target) -> right);
        while((*tmp)->left != NULL){ tmp = &((*tmp)->left); }
        (*target)->key = (*tmp)->key;

        Node* delete_tmp = (*tmp);
        *tmp = (*tmp) -> right;
        delete delete_tmp;

    } else {
        Node* tmp = *target;
        if((*target)->left != NULL){
            *target = (*target) -> left;
        } else {
            *target = (*target) -> right;
        }
        delete tmp;
    }

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int BinarySearchTree::_insert(Node *&target, int key) {
    if(target == NULL){
        target = new Node(key);
        return 0;
    } else if (key == target->key) {
        return 1;
    } else if (key < target->key){
        return _insert(target->left, key);
    } else if (key > target->key) {
        return _insert(target->right, key);
    }

    return 0;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
