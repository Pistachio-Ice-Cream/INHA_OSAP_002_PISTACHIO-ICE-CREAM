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
  value_type key;
  value_type key() {
    return key;
  }
};
template <typename value_type>
class treeNode : public Node {
 public:
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
  Node<value_type> *InsertNode(Node<value_type> *iterator,
                               value_type key_of_new_node);
  Node<value_type> *EraseNode(Node<value_type> *root_node,
                              value_type key_of_target);
  Node<value_type> *FindNodePtr(value_type find_target);
  int Minimum(value_type x);
  int Maximum(value_type x);
  void Rank(value_type x);
  void Erase(value_type x);
  int height(Node<value_type> *target_node);

 protected:
  int CalculateBalance(Node<value_type> *target_node);
  Node<value_type> *LeftRotation(Node<value_type> *old_axis);
  Node<value_type> *RightRotation(Node<value_type> *old_axis);
  void AdjustBlance(Node<value_type> *root, value_type target_key);
  int FindDepth(value_type find_target);

 protected:
  int node_counter_ = 0;
  Node<value_type> *root_;
};
#endif // AVL_TREE_H