/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23, rla1wo23@gmail.com}.
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <algorithm>
#include <iostream>

template <typename value_type>
class Node {
 public:
  value_type key() {
    return this->key_;
  }

 protected:
  value_type key_;
};
template <typename value_type>
class TreeNode : public Node {
 private:
  int height_ = 0;
  TreeNode *left_ = nullptr;
  TreeNode *right_ = nullptr;
  friend class AVLTree;
};
template <typename value_type>
class AVLTree {
 public:
  AVLTree();
  ~AVLTree();
  bool IsEmpty();
  int Size();
  TreeNode<value_type> *InsertNode(TreeNode<value_type> *iterator,
                                   value_type key_of_new_node);
  TreeNode<value_type> *EraseNode(TreeNode<value_type> *root_node,
                                  value_type key_of_target);
  TreeNode<value_type> *FindNodePtr(value_type find_target);
  int Minimum(value_type x);
  int Maximum(value_type x);
  void Rank(value_type x);
  void Erase(value_type x);
  int height(TreeNode<value_type> *target_node);

 protected:
  int CalculateBalance(TreeNode<value_type> *target_node);
  TreeNode<value_type> *LLRotation(TreeNode<value_type> *old_axis);
  TreeNode<value_type> *RRRotation(TreeNode<value_type> *old_axis);
  void AdjustBlance(TreeNode<value_type> *root, value_type target_key);
  int FindDepth(value_type find_target);

 protected:
  int node_counter_ = 0;
  TreeNode<value_type> *root_;
};
#endif // AVL_TREE_H