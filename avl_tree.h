/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23, rla1wo23@gmail.com}.
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <algorithm>
#include <iostream>

#include "nodes.h"

template <typename value_type>
class AVLTree {
 public:
  AVLTree() : root_(new TreeNode<value_type>){};
  AVLTree(const AVLTree& copy_target) : root_(CopyTree(copy_target.root()));
  ~AVLTree();
  TreeNode<value_type>* root() const {
    return root_;
  }
  bool IsEmpty() const {
    return node_counter_ == 0;
  }
  int Size() const {
    return node_counter_;
  }
  TreeNode<value_type>* InsertNode(TreeNode<value_type>* iterator,
                                   value_type key_of_new_node);
  // iterator=new_node로 설정하는 부분 한 줄 추가했습니다.
  TreeNode<value_type>* EraseNode(TreeNode<value_type>* iterator,
                                  value_type key_of_target);
  TreeNode<value_type>* FindNodePtr(value_type find_target) const;
  TreeNode<value_type>* Minimum(value_type x) const;
  TreeNode<value_type>* Maximum(value_type x) const;
  int Rank(TreeNode<value_type>* target_node, value_type x);
  int NodeHeight(TreeNode<value_type>* target_node) const;
  int FindDepth(value_type find_target) const;

 protected:
  int CalculateSize(TreeNode<value_type>* target_node) const;
  int CalculateHeight(TreeNode<value_type>* target_node) const;
  int CalculateBalance(TreeNode<value_type>* target_node) const;
  TreeNode<value_type>* LLRotation(TreeNode<value_type>*& old_axis);
  TreeNode<value_type>* RRRotation(TreeNode<value_type>*& old_axis);
  void AdjustBalance(TreeNode<value_type>*& axis, value_type& target_key);

 protected:
  int node_counter_ = 0;
  TreeNode<value_type>* root_;

  TreeNode<value_type>* CopyTree(const TreeNode<value_type>* node);
};
#endif