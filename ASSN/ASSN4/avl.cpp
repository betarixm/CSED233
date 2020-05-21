#include "tree.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

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
    balance(_root);

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
