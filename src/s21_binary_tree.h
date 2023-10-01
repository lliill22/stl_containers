#ifndef S21_CONTAINERS_BINARY_TREE_H
#define S21_CONTAINERS_BINARY_TREE_H

#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename key_, typename value_, typename compare_>
class BinaryTree {
 public:
  class Node;
  struct treeIterator;
  struct treeIteratorConst;

  using key_type = key_;
  using value_type = value_;

  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using iterator = treeIterator;
  using const_iterator = treeIteratorConst;

  BinaryTree() : root(new Node), size_(0){};

  BinaryTree(const BinaryTree &other) : root(nullptr), size_(other.size_) {
    root = root->copyNode(other.root);
  }

  BinaryTree(BinaryTree &&other) noexcept
      : root(other.root), size_(other.size_) {
    other.size_ = 0;
    other.root = new Node();
  }

  BinaryTree &operator=(const BinaryTree &other) {
    if (this != &other) {
      size_ = other.size_;
      root->copyNode(other.root);
    }
    return *this;
  };

  BinaryTree &operator=(BinaryTree &&other) noexcept {
    if (this != &other) {
      deleteTree();
      size_ = other.size_;
      root = other.root;

      other.size_ = 0;
      other.root = new Node();
    }
    return *this;
  }

  ~BinaryTree() { deleteTree(); }

  void deleteTree() {
    if (root) {
      size_ = 0;
      root->clearNode(root);
      root = nullptr;
    }
  }

  bool empty() const noexcept { return size_ == 0 ? true : false; }

  size_type size() const noexcept { return size_; }

  Node *minNode() const {
    if (empty()) return nullptr;
    return root->getMin();
  }

  std::pair<iterator, bool> insertUnique(value_type item) {
    std::pair<iterator, bool> result = insert(item, root, true);
    if (result.second == true) increaseSize();
    return result;
  }

  std::pair<iterator, bool> insertNonUnique(value_type item) {
    std::pair<iterator, bool> result = insert(item, root, false);
    if (result.second == true) increaseSize();
    return result;
  }

  std::pair<iterator, bool> insert(value_type item, Node *n, bool isUnique) {
    std::pair<iterator, bool> result = {iterator(n, root), true};
    if (empty()) {
      root->data = item;
      return result;
    }
    if (compare_Keys(item, n->data)) {
      if (n->left == nullptr) {
        n->left = new Node(item);
        n->left->parent = n;
      } else {
        result = insert(item, n->left, isUnique);
      }
    } else if (compare_Keys(n->data, item)) {
      if (n->right == nullptr) {
        n->right = new Node(item);
        n->right->parent = n;
      } else {
        result = insert(item, n->right, isUnique);
      }
    } else {
      if (isUnique == true) {
        result = {iterator(n, root), false};
      } else {
        if (n->right == nullptr) {
          n->right = new Node(item);
          n->right->parent = n;
        } else {
          result = insert(item, n->right, isUnique);
        }
      }
    }
    balance(n);
    return result;
  }

  void balance(Node *node) {
    node->updateHeight();
    int temp = node->bfactor();
    if (temp == 2) {
      if (node->right != nullptr) {
        if (node->right->bfactor() < 0) node->right = rotateRight(node->right);
      }
      node = rotateLeft(node);
    }
    if (temp == -2) {
      if (node->left != nullptr) {
        if (node->left->bfactor() > 0) node->left = rotateLeft(node->left);
      }
      node = rotateRight(node);
    }
  }

  Node *rotateRight(Node *p) {
    Node *q = p->left;
    if (root == p) {
      root = q;
    } else {
      if (p->parent->left == p) p->parent->left = q;
      if (p->parent->right == p) p->parent->right = q;
    }
    q->parent = p->parent;

    p->left = q->right;
    q->right = p;
    if (p->left) p->left->parent = q;
    p->parent = q;
    q->updateHeight();
    return q;
  }

  Node *rotateLeft(Node *q) {
    Node *p = q->right;
    if (root == q) {
      root = p;
    } else {
      if (q->parent->left == q) q->parent->left = p;
      if (q->parent->right == q) q->parent->right = p;
    }
    p->parent = q->parent;

    q->right = p->left;
    p->left = q;
    if (q->right) q->right->parent = q;
    q->parent = p;
    p->updateHeight();
    return p;
  }

  bool contains(const key_ &key) const {
    return root->search(key) ? true : false;
  }

  iterator find(const key_ &key) const {
    iterator it(root->search(key), root);
    if (it.iter == nullptr) throw std::out_of_range("no key found");
    return it;
  }

  void increaseSize() noexcept { size_++; }
  void decreaseSize() noexcept { size_--; }

  void erase(iterator pos) {
    Node *p = pos.iter;
    Node *newNode = remove(p);
    delete p;
    p = nullptr;
    if (newNode) balance(newNode);
    if (!root) root = new Node();
    decreaseSize();
  }

  Node *remove(Node *p) {
    Node *newNode = nullptr;
    if (p == nullptr) return newNode;

    if (p->left != nullptr && p->right != nullptr) {
      newNode = removeTwoChildNode(p);
    } else if ((p->left == nullptr) xor (p->right == nullptr)) {
      newNode = removeOneChildNode(p);
    }

    if (p != root) {
      (p->parent->left == p) ? p->parent->left = newNode
                             : p->parent->right = newNode;
    } else {
      root = newNode;
    }

    return newNode;
  }

  Node *removeOneChildNode(Node *p) {
    Node *newNode = (p->left == nullptr) ? p->right : p->left->getMax();
    newNode->parent = p->parent;
    return newNode;
  }

  Node *removeTwoChildNode(Node *p) {
    Node *maxInLeft = p->left->getMax();
    Node *newNode = maxInLeft;

    newNode->right = p->right;
    if (p->right) newNode->right->parent = newNode;

    maxInLeft->parent->right = maxInLeft->left;
    if (maxInLeft->left) maxInLeft->left->parent = maxInLeft->parent;

    newNode->parent = p->parent;

    if (p->left != newNode) {
      newNode->left = p->left;
      newNode->left->parent = newNode;
    }

    return newNode;
  }

  void clearTree() {
    if (root) {
      size_ = 0;
      root->clearNode(root);
    }
    root = new Node();
  }

  iterator findLowerBound(const_reference key) const {
    Node *start = root;
    Node *result = nullptr;

    while (start != nullptr) {
      if ((start->data >= key)) {
        result = start;
        start = start->left;
      } else {
        start = start->right;
      }
    }
    return iterator(result, root);
  }

  iterator findUpperBound(const_reference key) const {
    Node *start = root;
    Node *result = nullptr;
    while (start != nullptr) {
      if (start->data > key) {
        result = start;
        start = start->left;
      } else
        start = start->right;
    }

    return iterator(result, root);
  }

  size_type count(const key_ &key) const noexcept {
    return root->countNonUnique(key);
  }

  iterator at(const key_ &key) const {
    return iterator(root->getPair(key), root);
  }
  bool containsPair(const key_ &key) const {
    return root->getPair(key) ? true : false;
  }

  Node *getRoot() const noexcept { return root; }

  struct treeIterator {
    treeIterator() = delete;
    treeIterator(Node *node, Node *root_) : iter(node), root(root_){};

    reference operator*() {
      if (iter == nullptr && root != nullptr) {
        iter = root->getMax();
      }
      return iter->data;
    }

    iterator &operator++() {
      if (iter == nullptr && root != nullptr) {
        iter = root->getMax();
      }
      iter = iter->moveForward();
      return *this;
    }

    iterator &operator--() {
      if (iter == nullptr && root != nullptr) {
        iter = root->getMin();
      }
      iter = iter->moveBack();
      return *this;
    }

    bool operator==(const iterator &other) const noexcept {
      return iter == other.iter;
    }

    bool operator!=(const iterator &other) const noexcept {
      return iter != other.iter;
    }

    Node *iter;
    Node *root;
  };

  struct treeIteratorConst {
    treeIteratorConst() = delete;
    treeIteratorConst(Node *node, Node *root_) : iter(node), root(root_){};

    const_reference operator*() const {
      if (iter == nullptr && root != nullptr) {
        root->getMax();
      }
      return iter->data;
    }

    const_iterator &operator++() {
      if (iter == nullptr && root != nullptr) {
        iter = root->getMax();
      }
      iter = iter->moveForward();
      return *this;
    }

    const_iterator &operator--() {
      if (iter == nullptr && root != nullptr) {
        iter = root->getMin();
      }
      iter = iter->moveBack();
      return *this;
    }

    bool operator==(const_iterator &other) const noexcept {
      return iter == other.iter;
    }

    bool operator!=(const_iterator &other) const noexcept {
      return iter != other.iter;
    }

    const Node *iter;
    Node *root;
  };

 private:
  Node *root;
  size_type size_;
  compare_ compare_Keys;
};

template <typename key_, typename value_, typename compare_>
class BinaryTree<key_, value_, compare_>::Node {
 public:
  Node() = default;
  Node(value_type data_) : data(data_) {}

  Node *copyNode(const Node *other) {
    Node *copy = new Node{other->data};
    if (other->left) copy->left = copy->copyNode(other->left);
    if (other->right) copy->right = copy->copyNode(other->right);
    copy->parent = this;
    return copy;
  }

  Node *moveForward() const {
    Node *p = const_cast<Node *>(this);
    if (right != nullptr) {
      return right->getMin();
    } else {
      Node *tempParent = p->parent;
      while (tempParent != nullptr && tempParent->right == p) {
        p = tempParent;
        tempParent = tempParent->parent;
      }
      p = tempParent;
    }
    return p;
  }

  Node *moveBack() const {
    Node *p = const_cast<Node *>(this);
    if (left != nullptr) {
      return left->getMax();
    } else {
      Node *tempParent = p->parent;
      while (tempParent != nullptr && tempParent->left == p) {
        p = tempParent;
        tempParent = tempParent->parent;
      }
      p = parent;
    }
    return p;
  }

  Node *getMin() {
    if (left == nullptr) return this;
    return left->getMin();
  }

  Node *getMax() {
    if (right == nullptr) return this;
    return right->getMax();
  }

  int updateHeight() {
    int left_height = (left == nullptr) ? 0 : left->updateHeight();
    int right_height = (right == nullptr) ? 0 : right->updateHeight();
    height = 1 + std::max(left_height, right_height);
    return height;
  }

  int getHeight() const { return (this != nullptr) ? height : 0; }

  int bfactor() const { return right->getHeight() - left->getHeight(); }

  Node *search(const key_ &key) {
    if (data < key) {
      return (right == nullptr) ? nullptr : right->search(key);
    } else if (data > key) {
      return (left == nullptr) ? nullptr : left->search(key);
    } else {
      return this;
    }
  }

  size_type countNonUnique(const key_ &key) const noexcept {
    size_type count_left = (left == nullptr) ? 0 : left->countNonUnique(key);
    size_type count_right = (right == nullptr) ? 0 : right->countNonUnique(key);
    return (data == key ? 1 : 0) + count_left + count_right;
  }

  Node *getPair(const key_ &key) {
    Node *left_res = (left == nullptr) ? nullptr : left->getPair(key);
    Node *right_res = (right == nullptr) ? nullptr : right->getPair(key);
    if (data.first == key) return this;
    return (data.first < key) ? right_res : left_res;
  }

  void clearNode(Node *node) {
    if (node != nullptr) {
      clearNode(node->left);
      clearNode(node->right);
      delete node;
      node = nullptr;
    }
  }

  value_type data;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  int height = 0;
};
}  // namespace s21

#endif  // S21_CONTAINERS_BINARY_TREE_H