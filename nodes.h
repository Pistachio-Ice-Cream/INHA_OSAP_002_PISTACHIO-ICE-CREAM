#ifndef NODES_H
#define NODES_H
#include "avl_tree.h"
template <typename value_type>
class Node {
 public:
  value_type key() const {
    return this->key_;
  }
  void set_key(value_type new_key) {
    key_ = new_key;
  }

 protected:
  value_type key_;
};
// clean
template <typename value_type>
class AVLTree;

template <typename value_type>
class TreeNode : public Node<value_type> {
 public:
  int height() const {
    return height_;
  }
  void set_height(int new_height) {
    height_ = new_height;
  }
  int size() const {
    return size_;
  }
  void set_size(int new_size) {
    size_ = new_size;
  }

  bool LeftIsNull() {
    return left_ == nullptr;
  }
  bool RightIsNull() {
    return right_ == nullptr;
  }
  bool NoChild() {
    return ((left_ == nullptr) && (right_ == nullptr));
  }

 public:
  TreeNode* left_ = nullptr;
  TreeNode* right_ = nullptr;
  friend class AVLTree<value_type>;

 private:
  int height_ = 0;
  int size_ = 1;
};
#endif