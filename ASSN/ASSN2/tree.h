#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder();
  string postOrder();
  string inOrder();
  int getHeight();
  bool isComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  void append(Node* node, string& result);
  void _preOrder(Node* node, string& result);
  void _postOrder(Node* node, string& result);
  void _inOrder(Node* node, string& result);
  int _height(Node *node);
  void _isComplete(Node* node, bool& complete);
  void checkCompletePreOrder(Node *node, bool &complete, bool &isDone, int height, int depth);
        ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};