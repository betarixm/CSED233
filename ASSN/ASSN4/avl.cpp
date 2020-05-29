#include "tree.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

void AVLTree::balance(Node *target, int new_data) {
    if(target == NULL){
        return;
    } else if (new_data < target->key){
        balance(target->left, new_data);
    } else if (new_data > target->key) {
        balance(target->right, new_data);
    }

    setHeight(_root);
    _balance(target);
    setHeight(_root);
}

Node *AVLTree::_balance(Node *target) {
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

Node *AVLTree::rotate_left_right(Node *node) {
    node->left= rotate_left(node->left);
    return rotate_right(node);
}

Node *AVLTree::rotate_right_left(Node *node) {
    node->right= rotate_right(node->right);
    return rotate_left(node);

}

Node *AVLTree::rotate_left(Node *node) {

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

Node *AVLTree::rotate_right(Node *node) {

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

int AVLTree::getBf(Node *node) {
    if(_root == NULL) return -1;
    int left = node->left != NULL ? node->left->height : -1;
    int right = node->right != NULL ? node->right->height : -1;

    return left - right;
}

int AVLTree::setHeight(Node *target) {
    if(target == NULL){ return -1; }
    int left = (target->left != NULL) ? (setHeight(target->left)) : (0);
    int right = (target->right != NULL) ? (setHeight(target->right)) : (0);
    int _height = (target-> left == NULL && target->right == NULL) ? (0) : (max(left, right) + 1);
    target->height = _height;
    return _height;
}

Node **AVLTree::_getNodeByKey(Node **_node, int key) {
    if((*_node) == NULL) return NULL;
    if((*_node)->key == key) return _node;

    Node** tmp_1 = NULL;
    Node** tmp_2 = NULL;
    if((*_node)->left != NULL) tmp_1 = _getNodeByKey(&((*_node)->left), key);
    if((*_node)->right != NULL) tmp_2 = _getNodeByKey(&((*_node)->right), key);

    if(tmp_1 != NULL) return tmp_1;
    if(tmp_2 != NULL) return tmp_2;

    return NULL;
}

Node **AVLTree::getNodeByKey(int key) {
    return _getNodeByKey(&_root, key);
}

int AVLTree::_insert(Node *&target, int key) {
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
    if(res != 1){
        setHeight(_root);
        _balance(target);
        setHeight(_root);
    }

    return res;
}

int AVLTree::max(int x, int y) { return (x>y)?(x):(y); }

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return _insert(_root, key);

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node** target = getNodeByKey(key);
    if(target == nullptr) { return 1; }

    bool hasLeft = (*target)->left != nullptr;
    bool hasRight = (*target)->right != nullptr;

    if((!hasLeft) && (!hasRight)){
        delete * target;
        *target = NULL;
    } else if (hasLeft && hasRight) {
        Node** tmp = &((*target) -> left);
        while((*tmp)->right != NULL) { tmp = &((*tmp)->right); }
        (*target) -> key = (*tmp)->key;

        Node* delete_tmp = (*tmp);
        *tmp = (*tmp) -> left;
        delete delete_tmp;

    } else {
        Node* tmp = *target;
        *target = (tmp->left != NULL) ? (tmp->left) : (tmp->right);
        delete tmp;
    }

    setHeight(_root);
    balance(_root, key);

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


