#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string result;
  _preOrder(_root, result);
  result.pop_back();
  return result;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string result;
  _postOrder(_root, result);
  result.pop_back();
  return result;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string result;
  _inOrder(_root, result);
  result.pop_back();
  return result;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getHeight() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return _height(_root);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
bool BinaryTree::isComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  bool result = true;
  _isComplete(_root, result);
  return result;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */


void BinaryTree::append(Node *node, string &result) {
    result += node->value;
    result += " ";
}

void BinaryTree::_preOrder(Node* node, string& result){
    if(node != NULL) {
        append(node, result);
        _preOrder(node->left, result);
        _preOrder(node->right, result);
    }
}

void BinaryTree::_postOrder(Node *node, string &result) {
    if(node != NULL) {
        _postOrder(node->left, result);
        _postOrder(node->right, result);
        append(node, result);
    }
}

void BinaryTree::_inOrder(Node *node, string &result) {
    if(node != NULL) {
        _inOrder(node->left, result);
        append(node, result);
        _inOrder(node->right, result);
    }
}

int BinaryTree::_height(Node *node) {
    if(node == NULL){
        return -1;
    } else {
        return ((_height(node->left) > _height(node->right)) ? (_height(node->left)) : (_height(node->right))) + 1;
    }
}

void BinaryTree::_isComplete(Node *node, bool& complete){
    int height = this->getHeight();
    bool isDone = false;
    checkCompletePreOrder(node, complete, isDone, height, 0);
}

void BinaryTree::checkCompletePreOrder(Node *node, bool &complete, bool &isDone, int height, int depth) {
    if(!complete) return;
    if(node == NULL){
        complete = (height == depth || height == depth - 1);
    } else {
        if(depth == (height - 1)){
            if(isDone){
                complete = (node->left == NULL && node->right == NULL);
            } else {
                isDone = (node->left == NULL || node->right == NULL);
                complete = !(node->left == NULL && node->right != NULL);
            }
        } else if (depth != height) {
            complete = (node->left != NULL && node->right != NULL);
        }

        checkCompletePreOrder(node->left, complete, isDone, height, depth+1);
        checkCompletePreOrder(node->right, complete, isDone, height, depth+1);
    }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////