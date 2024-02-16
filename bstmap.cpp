// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <algorithm>
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { BSTMapHelper(root, bst.root); }

void BSTMap::BSTMapHelper(Node *&newNode, const Node *oldNode) {
  if (oldNode == nullptr) {
    newNode = nullptr;
    return;
  }
  newNode = new Node();
  newNode->data = oldNode->data;
  BSTMapHelper(newNode->left, oldNode->left);
  BSTMapHelper(newNode->right, oldNode->right);
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  if (v.empty()) {
    root = nullptr;
    return;
  }

  vector<value_type> sortedV = v;
  sort(sortedV.begin(), sortedV.end(),
       [](const value_type &a, const value_type &b) {
         return a.first < b.first;
       });
  root = nullptr;
  rebalanceHelper(sortedV, 0, static_cast<int>(sortedV.size()) - 1);
}

// A helper function to recursively delete all nodes in the binary search tree
// to clear the tree.
void BSTMap::removeAllTreeHelper(Node *currentNode) {
  if (currentNode == nullptr) {
    return;
  }

  removeAllTreeHelper(currentNode->left);
  removeAllTreeHelper(currentNode->right);

  delete currentNode;
}

// destructor
BSTMap::~BSTMap() {
  if (root == nullptr) {
    return;
  }

  removeAllTreeHelper(root);
}

// delete all nodes in tree
void BSTMap::clear() {
  if (root == nullptr) {
    return;
  }

  removeAllTreeHelper(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// A helper function for size
// Recursively calculates the size (number of nodes) of the binary search tree.
int BSTMap::sizeHelper(const Node *root) const {
  if (root == nullptr) {
    return 0;
  }

  return 1 + sizeHelper(root->left) + sizeHelper(root->right);
}

// Number of nodes in BST
int BSTMap::size() const { return sizeHelper(root); }

// true if item is in BST
// This function uses a while loop to traverse the tree. It follows the
// standard BST traversal logic to locate a node: if the key is less than
// the current node's key, it goes left; if greater, it goes right.
bool BSTMap::contains(const key_type &key) const {
  Node *currentNode = root;
  while (root != nullptr) {
    if (key < currentNode->data.first) {
      currentNode = currentNode->left;
    } else if (key > currentNode->data.first) {
      currentNode = currentNode->right;
    } else {
      return true;
    }
  }
  return false;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  Node *currentNode = root;
  while (currentNode != nullptr) {
    if (currentNode->data.first == k) {
      return currentNode->data.second;
    }

    // If 'k' is less than the key of the current node, search
    // in the left subtree.
    if (k < currentNode->data.first) {
      if (currentNode->left == nullptr) {
        currentNode->left =
            new Node{make_pair(k, mapped_type()), nullptr, nullptr};
        return currentNode->left->data.second;
      }
      currentNode = currentNode->left;
    } else {
      // If 'k' is greater than the key of the current node,
      // search in the right subtree.
      if (currentNode->right == nullptr) {
        currentNode->right =
            new Node{make_pair(k, mapped_type()), nullptr, nullptr};
        return currentNode->right->data.second;
      }
      currentNode = currentNode->right;
    }
  }

  root = new Node{make_pair(k, mapped_type()), nullptr, nullptr};
  return root->data.second;
}

// Recursively traverses the binary search tree (BST) to find and accumulate
// all key-value pairs where the key starts with a specified prefix.
// The function performs an inorder traversal of the BST.
vector<BSTMap::value_type> &
BSTMap::getHelper(Node *currentNode, const key_type &key,
                  vector<value_type> &accumulatedValues) const {
  if (currentNode == nullptr) {
    return accumulatedValues;
  }

  getHelper(currentNode->left, key, accumulatedValues);
  if (currentNode->data.first.compare(0, key.size(), key) == 0) {
    accumulatedValues.push_back(currentNode->data);
  }

  getHelper(currentNode->right, key, accumulatedValues);

  return accumulatedValues;
}

// returns a vector of key-value pairs that partially match the key
// Main function used by autocomplete
// Might traverse both left and right subbranches of a node
// Example: getall("hel")
// Return: { (hello, 10), (help, 20)}
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  return getHelper(root, k, v);
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }

  int leftHeight = getHeight(n->left);
  int rightHeight = getHeight(n->right);

  return 1 + max(leftHeight, rightHeight);
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  if (contains(k)) {
    return 1;
  }

  return 0;
}

// A helper function for inorder tranversal
void BSTMap::inorderHelper(void visit(const value_type &item),
                           Node *root) const {
  if (root == nullptr) {
    return;
  }
  inorderHelper(visit, root->left);
  visit(root->data);
  inorderHelper(visit, root->right);
}

// A helper function for preorder traversal
void BSTMap::preorderHelper(void visit(const value_type &item),
                            Node *root) const {
  if (root == nullptr) {
    return;
  }
  visit(root->data);
  preorderHelper(visit, root->left);
  preorderHelper(visit, root->right);
}

// A helper function for postorder traversal
void BSTMap::postorderHelper(void visit(const value_type &item),
                             Node *root) const {
  if (root == nullptr) {
    return;
  }
  postorderHelper(visit, root->left);
  postorderHelper(visit, root->right);
  visit(root->data);
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  return inorderHelper(visit, root);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  return preorderHelper(visit, root);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  return postorderHelper(visit, root);
}

// A helper function for insert
// Recursively inserts a new node with the specified item (key-value pair) into
// the binary search tree. This function maintains the BST property where for
// each node, all nodes in the left subtree have keys less than the node's key,
// and all nodes in the right subtree have keys greater than the node's key.
BSTMap::Node *BSTMap::insertHelper(const value_type &item, Node *currentNode) {
  if (currentNode == nullptr) {
    return new Node{item, nullptr, nullptr};
  }

  if (item.first < currentNode->data.first) {
    currentNode->left = insertHelper(item, currentNode->left);
  } else if (item.first > currentNode->data.first) {
    currentNode->right = insertHelper(item, currentNode->right);
  }

  return currentNode;
}

void BSTMap::insert(const value_type &item) { root = insertHelper(item, root); }

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> vec;
  vec = getAll("");
  clear();
  rebalanceHelper(vec, 0, static_cast<int>(vec.size()) - 1);
}

void BSTMap::rebalanceHelper(const vector<value_type> &elements, int start,
                             int end) {
  if (start > end) {
    return;
  }

  int mid = start + (end - start) / 2;
  insert(elements[mid]);

  rebalanceHelper(elements, start, mid - 1);
  rebalanceHelper(elements, mid + 1, end);
}

bool BSTMap::isSameTree(Node *p, Node *q) const {
  if (p == nullptr && q == nullptr) {
    return true;
  }

  if (p == nullptr || q == nullptr) {
    return false;
  }

  if (p->data != q->data) {
    return false;
  }

  bool left = isSameTree(p->left, q->left);
  bool right = isSameTree(p->right, q->right);

  return left && right;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return isSameTree(this->root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !isSameTree(this->root, other.root);
}
