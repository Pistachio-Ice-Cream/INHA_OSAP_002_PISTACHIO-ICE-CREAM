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
class treeNode {
 public:
  value_type get_key() {
    return this->key;
  }

 protected:
  value_type key;
};
template <typename value_type>
class treeNode : public Node {
 private:
  int height = 0;
  treeNode *left = nullptr;
  treeNode *right = nullptr;
  friend class AVLTree;
};
template <typename value_type>
class AVLTree {
 public:
  AVLTree();
  ~AVLTree();
  bool IsEmpty();
  int Size();
  treeNode<value_type> *InsertNode(treeNode<value_type> *iterator,
                                   value_type key_of_new_node);
  treeNode<value_type> *EraseNode(treeNode<value_type> *root_node,
                                  value_type key_of_target);
  treeNode<value_type> *FindNodePtr(value_type find_target);
  int Minimum(value_type x);
  int Maximum(value_type x);
  void Rank(value_type x);
  void Erase(value_type x);
  int height(treeNode<value_type> *target_node);

 protected:
  int CalculateBalance(treeNode<value_type> *target_node);
  treeNode<value_type> *LLRotation(treeNode<value_type> *old_axis);
  treeNode<value_type> *RRRotation(treeNode<value_type> *old_axis);
  void AdjustBlance(treeNode<value_type> *root, value_type target_key);
  int FindDepth(value_type find_target);

 protected:
  int node_counter_ = 0;
  treeNode<value_type> *root_;
};
#endif // AVL_TREE_H